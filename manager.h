#pragma once

template<typename T>
class Manager
{
public:
	static T* instance()//ʵ�ֵ���ģʽ
		//ֻ����ֻ�ܴ���һ��Manager����
		//�������ٴε���ֻ���ȡ�ӿ�
	{
		if (!manager)
			manager = new T();//�̲߳���ȫ
		//�ڶ��߳��п��ܻ���ֶ���߳�ͬʱͨ���жϵĿ�����

		return manager;
	}

private:
	static T* manager;

protected:
	Manager() = default;
	~Manager() = default;
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
};

template<typename T>
T* Manager<T>::manager = nullptr;


