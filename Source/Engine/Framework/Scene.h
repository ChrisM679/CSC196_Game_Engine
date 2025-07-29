#pragma once
#include "../Core/StringHelper.h"
#include <string>
#include <vector>
#include <memory>

namespace viper {
	class Actor;

	class Scene {
	public:
		Scene() = default;

		void Update(float dt);
		void Draw(class Renderer& renderer);
			
		void AddActor(std::unique_ptr<Actor> actor);
		void RemoveAllActors();

		template<typename T = Actor>
		T* GetactorByName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> GetActorsByTag(const std::string& tag);

	private:
		std::vector<std::unique_ptr<Actor>> m_actors;
	};

	template<typename T>
	inline T* Scene::GetactorByName(const std::string& name)
	{
		for (auto& actor : m_actors) {
			if (tolower(actor->name) == tolower(name)) {
				T* object = dynamic_cast<T*>(actor.get());
				if (object) {
					return object;
				}
			}
		}
		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Scene::GetActorsByTag(const std::string& tag) {
		std::vector<T*> results;
		for (auto& actor : m_actors) {
			if (tolower(actor->tag) == tolower(tag)) {
				T* object = dynamic_cast<T*>(actor.get());
				if (object) {
					results.push_back(object);
				}
			}
		}
		return results;
	}
}