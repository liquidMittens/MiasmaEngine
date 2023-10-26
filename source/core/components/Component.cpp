#include "components/Component.h"

using namespace Miasma::RTTI;

const std::size_t Component::Type = std::hash<std::string>()(TO_STRING(Component));
