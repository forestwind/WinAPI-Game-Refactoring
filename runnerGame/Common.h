#pragma once

// ���� ���ø� �̱��� ����
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



/////////////////	 ����ü ���𱸰�	////////////////

typedef struct _BOOM{  //������Ʈ ����ü ����
	int use;  //���������
	int boomcount;
	POINT Start;  //��ŸƮ ��ǥ
	POINT size;   // ������

}BOOM;



typedef struct _UserHbit{
	HBITMAP b_background[3], b_object, b_Enemy, b_gundam, b_title, b_interface, b_ending, b_boom;
}UserHbit;
