#pragma once

// 동적 템플릿 싱글톤 패턴
template <typename T>
class Singleton{
protected:
	Singleton() {}
	virtual ~Singleton() {}
public :

	static T* GetInstance() 
	{
		if (m_pInstance == NULL) {
			m_pInstance = new T;
		}
			return m_pInstance;
		
	}

	static void DestroyInstance() 
	{
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

private :
	static T* m_pInstance;
};

template <typename T> 
T* Singleton <T>::m_pInstance = 0;



/////////////////	 구조체 선언구간	////////////////

typedef struct _BOOM{  //오브젝트 구조체 설정
	int use;  //사용중인지
	int boomcount;
	POINT Start;  //스타트 좌표
	POINT size;   // 사이즈

}BOOM;



typedef struct _UserHbit{
	HBITMAP b_background[3], b_object, b_Enemy, b_gundam, b_title, b_interface, b_ending, b_boom;
}UserHbit;
