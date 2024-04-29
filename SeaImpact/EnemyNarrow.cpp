#include "EnemyNarrow.h"

EnemyNarrow::EnemyNarrow(const Coordinates& pos, std::vector<Shot>* shots) : Enemy(pos, { ("# "), ("##"), ("# ") }, pos.Y, pos.Y, true, 5, 70, shots, 300, 1)
{
}