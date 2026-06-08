// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/PMGameplayTags.h"

namespace PMGameplayTags
{

	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move,"InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look,"InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack,"InputTag.Attack");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip_LightSword,"InputTag.Equip.LightSword");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnEquip_LightSword,"InputTag.UnEquip.LightSword");

	/** Action Tags 招式连段Tag **/
	UE_DEFINE_GAMEPLAY_TAG(ActionTag,"ActionTag");
	
	/** Player Tags **/
	UE_DEFINE_GAMEPLAY_TAG(PM_Ability_Action,"PM.Ability.Action");
	
	UE_DEFINE_GAMEPLAY_TAG(PM_Weapon_LightSword,"PM.Weapon.LightSword");

	UE_DEFINE_GAMEPLAY_TAG(PM_Event_Equip_LightSword,"PM.Event.Equip.LightSword");
	UE_DEFINE_GAMEPLAY_TAG(PM_Event_UnEquip_LightSword,"PM.Event.UnEquip.LightSword");

	UE_DEFINE_GAMEPLAY_TAG(PM_State_Action,"PM.State.Action");
	UE_DEFINE_GAMEPLAY_TAG(PM_State_Action_IsMoving,"PM.State.Action.IsMoving");

	/** Enemy Tags **/
	UE_DEFINE_GAMEPLAY_TAG(PM_Enemy_Weapon,"PM.Enemy.Weapon");
	
	UE_DEFINE_GAMEPLAY_TAG(PM_Enemy_Action,"PM.Enemy.Action");
	
	UE_DEFINE_GAMEPLAY_TAG(PM_Enemy_State,"PM.Enemy.State");

	UE_DEFINE_GAMEPLAY_TAG(PM_Enemy_Event,"PM.Enemy.Event");
	
	
}