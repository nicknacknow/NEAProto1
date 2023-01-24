#pragma once

template <class T>
class Singleton {
public:
	static T* GetSingleton() {
		static T* singleton = nullptr;
		if (singleton == nullptr)
			singleton = new T();
		return singleton;
	}
};