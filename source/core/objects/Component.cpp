#include "core\objects\Component.h"

using namespace miasma_rtti;

const std::size_t Component::Type = std::hash<std::string>()(TO_STRING(Component));
