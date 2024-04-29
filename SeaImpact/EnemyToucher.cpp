#include "EnemyToucher.h"

EnemyToucher::EnemyToucher(const Coordinates& pos, std::vector<Shot>* shots) : Enemy(pos, { ("##"), ("# "), ("##") }, GameRender::Height-4, 0, true, 5, 50, shots, 800, 1)
{
}