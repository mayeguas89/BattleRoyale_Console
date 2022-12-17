#include "player.h"

#include "turn_action.h"

TurnActionType Player::DoAction()
{
  if (character_)
    return character_->DoAction();
  return TurnActionType::None;
}
