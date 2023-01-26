#pragma once

template <class T>
class Singleton {
public:
	/**
	 * @brief allows classes to be grabbed and singularised
	 * @return initiates or returns static class
	*/
	template<class ...A> // add vararg to singleton initiation
	static T* GetSingleton(A... arg) {
		static T* singleton = nullptr; 
		if (singleton == nullptr) // if its first time being called, instantiate singleton
			singleton = new T(arg...);
		return singleton;
	}
};