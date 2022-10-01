#include "Alien.hpp"

#include "Bullet.hpp"
#include "Camera.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include "Minion.hpp"
#include "Sound.hpp"
#include "Sprite.hpp"
#include <math.h>

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int numMinions, weak_ptr<GameObject> pbody) : Component(associated) {
  // Sprite
  Sprite *sp = new Sprite(associated, "assets/img/alien.png");
  associated.AddComponent(sp);

  // Collider
  Collider *col = new Collider(associated, { 0.6, 0.6 });
  associated.AddComponent(col);

  hp       = ALIEN_HP;
  nMinions = numMinions;
  speed.x  = 0.00004;
  speed.y  = 0.00004;
  pos.x    = associated.box.GetMiddleX();
  pos.y    = associated.box.GetMiddleY();
  this->pbody = pbody;

  state     = AlienState::RESTING;
  restTimer = Timer();

  alienCount++;
}

Alien::~Alien() {
  minionArray.clear();
  alienCount--;
}

void Alien::Start() {
  Game &game = Game::GetInstance();
  weak_ptr<GameObject> alienCenter = game.GetState().GetObjectPtr(&associated);

  if (!alienCenter.lock()) {
    return;
  }

  float darc = 360 / nMinions;

  for (int i = 0; i < nMinions; i++) {
    GameObject *minionGo = new GameObject();

    Minion *minion = new Minion(*minionGo, alienCenter, i * darc);
    minionGo->AddComponent(minion);

    minionArray.push_back(game.GetState().AddObject(minionGo));
  }
}

void Alien::Update(float dt) {
  if (pbody.expired())
    return;

  if (state == AlienState::RESTING) {
    restTimer.Update(dt);

    if (restTimer.Get() >= ALIEN_RESTING_TIME) {
      Camera &camera = Camera::GetInstance();
      cout << "Parou de descansar!" << endl;
      destination = { pbody.lock()->box.GetMiddleX() - camera.pos.x, pbody.lock()->box.GetMiddleY() - camera.pos.y};
      cout << "Dx: " << destination.x << ", Dy: " << destination.y << endl;
      state = AlienState::MOVING;

    }
  } else {
    float angle = atan2(destination.y - pos.y, destination.x - pos.x);
    float dx = speed.x * cos(angle) * dt;
    float dy = speed.y * sin(angle) * dt;

    bool withinLimitsX = abs(pos.x - destination.x) < dx;
    bool withinLimitsY = abs(pos.y - destination.y) < dy;

    if (withinLimitsX || withinLimitsY) {
      cout << "Chegou ao destino!" << endl;
      pos.x = destination.x;
      pos.y = destination.y;

      destination = { pbody.lock()->box.GetMiddleX(), pbody.lock()->box.GetMiddleY()};

      Minion *minion = (Minion *) minionArray[rand() % minionArray.size()].lock().get()->GetComponent("Minion");
      minion->Shoot(destination);

      restTimer.Restart();
      state = AlienState::RESTING;

    } else {
      pos.x += dx;
      pos.y += dy;
    }
  }

  // Girar lentamente
  associated.angleDeg -= DESLOCAMENTO_ARCO / 4;

  // Remover Alien por dano
  if (hp <= 0)
    associated.RequestDelete();

  if (associated.IsDead()) {
    Game &game = Game::GetInstance();
    GameObject *explosionGo = new GameObject();
    explosionGo->box.x = associated.box.x;
    explosionGo->box.y = associated.box.y;
    
    Sprite *explosion = new Sprite(*explosionGo, "assets/img/aliendeath.png", 4, 800000.0, 32.0);
    explosionGo->AddComponent(explosion);

    Sound *sound = new Sound(*explosionGo, "assets/audio/boom.wav");
    explosionGo->AddComponent(sound);

    if (sound != nullptr)
      sound->Play();

    game.GetState().AddObject(explosionGo);
  }
}

void Alien::Render() {
  Camera &camera = Camera::GetInstance();

  associated.box.x = pos.x + camera.pos.x - associated.box.w/2;
  associated.box.y = pos.y + camera.pos.y - associated.box.h/2;
}

bool Alien::Is(string type) {
  return type == "Alien";
}

void Alien::NotifyCollision(GameObject &other) {
  if (other.GetComponent("Bullet") != nullptr) {
    Bullet *bullet = (Bullet*) other.GetComponent("Bullet");

    if (bullet->targetsPlayer)
      return;

    hp -= bullet->GetDamage();
  }
}

void Alien::RemoveMinion(weak_ptr<GameObject> minion) {
  for (int i = minionArray.size() - 1; i >= 0; i--)
    if (minionArray[i].lock() == minion.lock())
      minionArray.erase(minionArray.begin() + i);
}
