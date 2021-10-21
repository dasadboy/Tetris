#include <algorithm>
#include "pieces.h"


// Square

const std::vector<int> Square::state_x = { 0, 1, 0, 1 };

const std::vector<int> Square::state_y = { 0, 0, 1, 1 };


// TBlock

const std::vector<int> TBlock::state_x = { -1, 0, 1, 0, 0, 0, 0, 1, -1, 0, 1, 0, 0, 0, 0, -1 };

const std::vector<int> TBlock::state_y = { 0, 0, 0, 1, 1, 0, -1, 0, 0, 0, 0, -1, 1, 0, -1, 0 };


// LBlockL

const std::vector<int> LBlockL::state_x = { -1, 0, 1, 1, 0, 0, 0, 1, -1, 0, 1, -1, 0, 0, 0, -1 };

const std::vector<int> LBlockL::state_y = { 0, 0, 0, 1, 1, 0, -1, -1, 0, 0, 0, -1, -1, 0, 1, 1 };


// LBlockR

const std::vector<int> LBlockR::state_x = { -1, 0, 1, -1, 0, 0, 0, 1, -1, 0, 1, 1, 0, 0, 0, -1 };

const std::vector<int> LBlockR::state_y = { 0, 0, 0, 1, 1, 0, -1, 1, 0, 0, 0, -1, -1, 0, 1, -1 };