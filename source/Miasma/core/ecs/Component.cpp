#include <Miasma/core/ecs/Component.h>

using namespace Miasma::Component;

const std::size_t Component::Type = std::hash<std::string>()(TO_STRING(Component));
