modded class ActionDropItem : ActionSingleUseBase{
	
	override void OnExecuteServer(ActionData action_data) {
		super.OnExecuteServer(action_data);

		// Ваши сообщения
		Print("[Yamori_DropDebug] !!! Author of the correction of the podification Yamori_ko !!!");
		Print("[Yamori_DropDebug] !!! If my modification is fully functional, please give me a star and subscribe to my GitHub. !!!");
		Print("[Yamori_DropDebug] !!! https://github.com/kopubarodeveloper !!!");
		Print("[Yamori_DropDebug] !!! Автор исправления модификации Yamori_ko !!!");
		Print("[Yamori_DropDebug] !!! Если моя модификация полностью функциональна, пожалуйста, поставьте мне звездочку и подпишитесь на мой GitHub. !!!");
		Print("[Yamori_DropDebug] !!! https://github.com/kopubarodeveloper !!!");

		Print("[DropDebug] === ActionDropItem.OnExecuteServer called ===");
		
		if(!action_data.m_Player) {
			Print("[DropDebug] Player is NULL");
			return;
		}
		
		if(!m_LogConfig || !m_LogConfig.ServerConfig) {
			Print("[DropDebug] Config is NULL");
			return;
		}
		
		Print("[DropDebug] ShowDropStorage = " + m_LogConfig.ServerConfig.ShowDropStorage);
		if(!m_LogConfig.ServerConfig.ShowDropStorage) {
			Print("[DropDebug] ShowDropStorage is false, returning");
			return;
		}
		
		// Пробуем разные способы получить предмет
		EntityAI itemObject = NULL;
		
		// Способ 1: Из m_MainItem (убрали каст)
		if(action_data.m_MainItem) {
			itemObject = action_data.m_MainItem; // БЕЗ EntityAI.Cast()
			Print("[DropDebug] Got item from m_MainItem");
		}
		
		// Способ 2: Из рук игрока
		if(!itemObject) {
			itemObject = action_data.m_Player.GetItemInHands();
			Print("[DropDebug] Got item from GetItemInHands");
		}
		
		// Способ 3: Из m_Target (здесь каст нужен)
		if(!itemObject && action_data.m_Target) {
			itemObject = EntityAI.Cast(action_data.m_Target.GetObject());
			Print("[DropDebug] Got item from m_Target.GetObject()");
		}
		
		if(!itemObject) {
			Print("[DropDebug] Could not get item object from any source");
			return;
		}
		
		string itemType = itemObject.GetType();
		Print("[DropDebug] Item type = " + itemType);
		
		if(!m_LogConfig.CustomConfig) {
			Print("[DropDebug] CustomConfig is NULL");
			return;
		}
		
		Print("[DropDebug] DropMonitorItems count = " + m_LogConfig.CustomConfig.DropMonitorItems.Count());
		Print("[DropDebug] SimpleLogsStorage = " + m_LogConfig.ServerConfig.SimpleLogsStorage);
		
		// Проверяем, пуст ли список - если пуст, логируем всё
		if(m_LogConfig.CustomConfig.DropMonitorItems.Count() == 0) {
			Print("[DropDebug] DropMonitorItems is empty, logging all items");
			if(!m_LogConfig.ServerConfig.SimpleLogsStorage){
				SendToCFTools(action_data.m_Player, "", string.Format("%1", itemObject), "Dropped");
			} else {
				SendToCFTools(action_data.m_Player, "", string.Format("%1", itemType), "Dropped");
			}
			return;
		}
		
		// Логика проверки
		if(!m_LogConfig.ServerConfig.SimpleLogsStorage){
			Print("[DropDebug] Checking with full item details");
			foreach(string CheckItem: m_LogConfig.CustomConfig.DropMonitorItems){
				if(CheckItem == "") continue;

				if(itemType.Contains(CheckItem)){
					Print("[DropDebug] MATCH FOUND! Sending to CFTools");
					SendToCFTools(action_data.m_Player, "", string.Format("%1", itemObject), "Dropped");
					return;
				}
			}
		}
		else{
			Print("[DropDebug] Checking with basic info");
			foreach(string CheckItem2: m_LogConfig.CustomConfig.DropMonitorItems){
				if(CheckItem2 == "") continue;

				if(itemType.Contains(CheckItem2)){
					Print("[DropDebug] MATCH FOUND! Sending to CFTools");
					SendToCFTools(action_data.m_Player, "", string.Format("%1", itemType), "Dropped");
					return;
				}
			}
		}
		
		Print("[DropDebug] No matches found in DropMonitorItems");
	}
}