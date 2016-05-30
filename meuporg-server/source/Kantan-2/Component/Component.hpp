#ifndef KANTAN_COMPONENT
#define KANTAN_COMPONENT

#include <string>
#include <vector>
#include <algorithm>

namespace kantan
{
	/**
		Component class.
	**/
	class Component
	{
        public:
            // Returns the component with the same owner id.
            // Returns nullptr if none.
            template<typename T>
            static T* getFirstComponentOwnedBy(std::size_t ownerId, std::vector<T*>& components)
            {
                // We look for the corresponding component, if it exists.
                auto cItr = std::find_if(components.begin(),
                                                              components.end(),
                                                              [ownerId](T* c) {
                                                                return c->getOwnerId() == ownerId;
                                                              });

                // If none found, returns nullptr.
                if(cItr == components.end())
                    return nullptr;

                return (*cItr);
            }

		public:
			// Ctor.
			Component(std::string name = "Unknown", std::size_t ownerId = (-1));

			// Dtor.
			virtual ~Component();

			// Name.
			std::string getName() const;

			// Owner id.
			std::size_t getOwnerId() const;

		protected:
		    // The name of the component.
			std::string m_name;

			// The id of the entity owning the component.
            std::size_t m_ownerId;
	};

} // namespace kantan.

#endif // KANTAN_COMPONENT
