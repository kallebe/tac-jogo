#include "PenguinBody.hpp"

#include "Bullet.hpp"
#include "Camera.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "GameData.hpp"
#include "InputManager.hpp"
#include "PenguinCannon.hpp"
#include "Sound.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "TileMap.hpp"
#include <math.h>

PenguinBody::PenguinBody(GameObject &associated) : Component(associated) {
  // Sprite
  Sprite *sp = new Sprite(associated, "assets/img/penguin.png");
  associated.AddComponent(sp);

  // Collider
  Collider *col = new Collider(associated);
  associated.AddComponent(col);

  speed.x     = 0.0;
  speed.y     = 0.0;
  pos.x       = associated.box.x;
  pos.y       = associated.box.y;
  linearSpeed = 0.0;
  hp          = PENGUIN_HP;
  angle       = 0;
  player      = this;
}

PenguinBody::~PenguinBody() {
  player = nullptr;
}

void PenguinBody::Start() {
  Game &game = Game::GetInstance();
  weak_ptr<GameObject> pbody = game.GetCurrentState().GetObjectPtr(&associated);

  GameObject *pcGo = new GameObject();

  PenguinCannon *penguinCannon = new PenguinCannon(*pcGo, pbody);
  pcGo->AddComponent(penguinCannon);

  game.GetCurrentState().AddObject(pcGo);

  pcannon = game.GetCurrentState().GetObjectPtr(pcGo);

  // Texto para mudança de tela
  GameObject *textGo = new GameObject();
  textGo->box.x = 0.1 * SCREEN_WIDTH;
  textGo->box.y = 0.1 * SCREEN_HEIGHT;

  Text *continueText = new Text(*textGo, "assets/font/Call me maybe.ttf", 24, Text::BLENDED, "HP " + to_string(hp), { 186, 37, 7, 255 });
  textGo->box.x -= textGo->box.w/2;
  textGo->box.y -= textGo->box.h/2;
  textGo->AddComponent(continueText);

  game.GetCurrentState().AddObject(textGo);

  textHp = game.GetCurrentState().GetObjectPtr(textGo);

  // Follow Penguin
  Camera &camera = Camera::GetInstance();
  camera.Follow(&associated);
}

void PenguinBody::Update(float dt) {
  InputManager &input = InputManager::GetInstance();

  if (input.IsKeyDown(FOWARD_W_KEY)) {
    speed.x = min(PENGUIN_ACCELERATION * abs(cos(angle * M_PI / 180)) + speed.x, MAX_PENGUIN_SPEED);
    speed.y = min(PENGUIN_ACCELERATION * abs(sin(angle * M_PI / 180)) + speed.y, MAX_PENGUIN_SPEED);
  }
  else if (input.IsKeyDown(BACKWARD_S_KEY)) {
    speed.x = max(speed.x - (PENGUIN_ACCELERATION * abs(cos(angle * M_PI / 180))), 0.0);
    speed.y = max(speed.y - (PENGUIN_ACCELERATION * abs(sin(angle * M_PI / 180))), 0.0);
  }
  else if (input.IsKeyDown(CLOCKWISE_D_KEY)) {
    angle += PENGUIN_ANGULAR_SPEED * dt;
    associated.angleDeg = angle;
  }
  else if (input.IsKeyDown(COUNTERCLOCKWISE_A_KEY)) {
    angle -= PENGUIN_ANGULAR_SPEED * dt;
    associated.angleDeg = angle;
  }

  // Atualiza posição
  Vec2 dpos;
  dpos.x = speed.x * cos(angle * M_PI / 180) * dt;
  dpos.y = speed.y * sin(angle * M_PI / 180) * dt;

  if (pos.x + dpos.x > 0 && pos.x + dpos.x < TILEMAP_WIDTH)
    pos.x += dpos.x;
  if (pos.y + dpos.y > 0 && pos.y + dpos.y < TILEMAP_HEIGHT)
    pos.y += dpos.y;

  Camera &camera = Camera::GetInstance();

  associated.box.x = pos.x + camera.pos.x - associated.box.w/2;
  associated.box.y = pos.y + camera.pos.y - associated.box.h/2;
}

void PenguinBody::NotifyCollision(GameObject &other) {
  if (other.GetComponent("Bullet") != nullptr) {
    Camera &camera = Camera::GetInstance();
    Bullet *bullet = (Bullet*) other.GetComponent("Bullet");

    if (!bullet->targetsPlayer)
      return;

    hp -= bullet->GetDamage();
    GameData::playerHp = hp;

    if (textHp.lock()) {
      Text *hpText = (Text*) textHp.lock()->GetComponent("Text");
      hpText->SetText("HP " + to_string(hp));
    }

    // Deleção por hp
    if (hp <= 0) {
      camera.Unfollow();
      textHp.lock()->RequestDelete();
      pcannon.lock()->RequestDelete();
      associated.RequestDelete();

      if (associated.IsDead()) {
        Game &game = Game::GetInstance();
        GameObject *explosionGo = new GameObject();
        explosionGo->box.x = associated.box.x;
        explosionGo->box.y = associated.box.y;
        
        Sprite *explosion = new Sprite(*explosionGo, "assets/img/penguindeath.png", 5, 2.0, 10.0);
        explosionGo->AddComponent(explosion);

        Sound *sound = new Sound(*explosionGo, "assets/audio/boom.wav");
        explosionGo->AddComponent(sound);

        if (sound != nullptr)
          sound->Play();

        game.GetCurrentState().AddObject(explosionGo);
      }
    }
  }
}

Vec2 PenguinBody::GetPos() {
  return pos;
}

void PenguinBody::Render() {
}

bool PenguinBody::Is(string type) {
  return type == "PenguinBody";
}
