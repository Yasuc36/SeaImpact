#include "EnemyWiggler.h"

EnemyWiggler::EnemyWiggler(const Coordinates& pos, std::vector<Shot>* shots) : Enemy(pos, { ("##"), ("##") }, pos.Y+3, pos.Y-3, true, 5, 70, shots, 1400, 1)
{
}