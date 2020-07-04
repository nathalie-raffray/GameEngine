#pragma once
#include "AssetStorage.h"
#include "Prefab.h"

#define FROMJSON(component) if (has_field<json>(j, #component))\
							{\
								if(!entity.has<component>()) entity.add<component>();\
								*entity.get<component>() = j.at(#component);\
							}
#define FROMJSON_PREFABCOMPONENT() if (has_field<json>(j, "PrefabComponent"))\
											{\
												entity.add<PrefabComponent>();\
												*entity.get<PrefabComponent>() = j.at("PrefabComponent");\
												auto& id = entity.get<PrefabComponent>()->prefab_id;\
												Prefab* prefab = Game::assets->get<Prefab>(id);\
												prefab->entity_immutable.clone(&entity);\
												prefab->entity_programmable.clone(&entity);\
											}

#define FROMJSON_EXPAND(component, __V_ARGS__) FROMJSON(component); FROMJSON_EXPAND(__V_ARGS__)

#define TOJSON(component) if(entity.has<component>()){\
								if(entity.has<PrefabComponent>())\
								{\
									auto& id = entity.get<PrefabComponent>()->prefab_id;\
									Prefab* prefab = Game::assets->get<Prefab>(id); \
									if(!prefab->entity_immutable.has<component>())\
									{\
										j[#component] = *entity.get<component>(); \
									}\
								}\
								else{\
									j[#component] = *entity.get<component>();\
								}\
						 }
#define TOJSON_EXPAND(component, __V_ARGS__) TOJSON(component); TOJSON_EXPAND(__V_ARGS__)
