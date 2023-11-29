#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>
#include <functional>
#include <vector>
#include <memory>
#include <algorithm>

#define TO_STRING( x ) #x
class GameObject;

//****************
// CLASS_DECLARATION
//
// This macro must be included in the declaration of any subclass of Component.
// It declares variables used in type checking.
//****************
#define CLASS_DECLARATION( classname )                                                      \
public:                                                                                     \
    static const std::size_t Type;                                                          \
    virtual bool IsClassType( const std::size_t classType ) const override;                 \

//****************
// CLASS_DEFINITION
// 
// This macro must be included in the class definition to properly initialize 
// variables used in type checking. Take special care to ensure that the 
// proper parentclass is indicated or the run-time type information will be
// incorrect. Only works on single-inheritance RTTI.
//****************
#define CLASS_DEFINITION( parentclass, childclass )                                         \
const std::size_t childclass::Type = std::hash< std::string >()( TO_STRING( childclass ) ); \
bool childclass::IsClassType( const std::size_t classType ) const {                         \
        if ( classType == childclass::Type )                                                \
            return true;                                                                    \
        return parentclass::IsClassType( classType );                                       \
}

namespace Miasma::Component {

	//***************
	// Component
	// base class
	//***************
	class Component {
	public:

		static const std::size_t Type;
		Component(GameObject* owner, std::string&& initialValue)
			: value(initialValue), 
			gameObject(owner), 
			active(true)
		{
		}
		virtual ~Component() = default;

		virtual bool IsClassType(const std::size_t classType) const {
			return classType == Type;
		}

		// behavior functions
		virtual void Start() = 0;
		virtual void Update(float dt) = 0;
		virtual void Shutdown() = 0;

		void SetActive(bool isActive) { active = isActive; }
		bool IsActive() const { return active; }
	public:

		std::string value = "uninitialized";
		GameObject* gameObject;

	protected:
		bool active;
	};
}

#endif
