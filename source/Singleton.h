#pragma once
#pragma once

template<class T>
class Singleton
{
public:
    Singleton() = default;
    ~Singleton() = default;
    Singleton(Singleton const&) = delete;
    void operator=(Singleton const&) = delete;


    static T* GetInstance()
    {
        if (m_pInstance == nullptr)
            m_pInstance = new T();

        return m_pInstance;
    }

    static void Destroy()
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }


private:
    static T* m_pInstance;
};


//Default singleton to nullptr.
template<typename T>
T* Singleton<T>::m_pInstance = nullptr;