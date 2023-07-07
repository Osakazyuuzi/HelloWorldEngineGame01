#ifndef ___OBJECT_H___
#define ___OBJECT_H___

#include <iostream>
#include <typeinfo>
#include <memory>
#include <list>
#include <string>
#include "ComponentBase.h" 
#include "TagName.h"

class ObjectManager;

class ObjectBase
{
	friend class ObjectManager;
	using ComponentPool = std::list<std::shared_ptr<ComponentBase>>;
public:
	// �R���X�g���N�^
	ObjectBase();
	// �����t���R���X�g���N�^
	ObjectBase(std::string name, std::string tag)
		: ObjectBase()
	{
		m_name = name;
		m_tag = tag;
	}
	// �f�X�g���N�^
	virtual ~ObjectBase(){}

	// �I�u�W�F�N�g���폜����
	void Destroy();
	void Start() {
		for (auto it = m_ComponentPool.begin(); it != m_ComponentPool.end(); it++)
			(*it)->Start();
	}
	// �R���|�[�l���g�̑O�X�V����
	void FixedUpdate()
	{
		for (auto it = m_ComponentPool.begin(); it != m_ComponentPool.end(); it++)
			(*it)->FixedUpdate();
	}
	// �R���|�[�l���g�̍X�V����
	void Update();
	// �R���|�[�l���g�̌�X�V����
	void LateUpdate() {
		for (auto it = m_ComponentPool.begin(); it != m_ComponentPool.end(); it++)
			(*it)->LateUpdate();
	}
	// �`��
	virtual void Draw() {};

	// �R���|�[�l���g��ǉ�
	template <class T>
	std::shared_ptr<T> AddComponent() {
		// �R���|�[�l���g���쐬�i�������m�ہj
		std::shared_ptr<T> pComp = std::make_shared<T>();
		// �����̃|�C���^���Z�b�g
		pComp->SetOwner(this);
		// �R���|�[�l���g�v�[���ɒǉ�
		m_ComponentPool.push_back(pComp);
		// �X�}�[�g�|�C���^��Ԃ�
		return pComp;
	}
	// �R���|�[�l���g���擾
	template <class T>
	std::shared_ptr<T> GetComponent() {
		// �v�[���𔽕�����
		for (auto it = m_ComponentPool.begin(); it != m_ComponentPool.end(); it++)
			// �����^�̃R���|�[�l���g������
			if (typeid(T) == typeid(*(*it))) 
				// ����������X�}�[�g�|�C���^��Ԃ�
				return std::static_pointer_cast<T>(*it);
		// ������Ȃ�������nullptr��Ԃ�
		return nullptr;
	}
	// �R���|�[�l���g�������Ă��邩
	template <class T>
	bool HasComponent() {
		// �v�[���𔽕�����
		for (auto it = m_ComponentPool.begin(); it != m_ComponentPool.end(); it++)
			// �����^�̃R���|�[�l���g�f�[�^������
			if (typeid(T) == typeid(*(*it)))
				// ����������true��Ԃ�
				return true;
		// ������Ȃ�������false��Ԃ�
		return false;
	}
	// �R���|�[�l���g��j��
	template <class T>
	bool RemoveComponent() {
		// �v�[���𔽕�����
		for (auto it = m_ComponentPool.begin(); it != m_ComponentPool.end(); it++)
			// �����^�̃R���|�[�l���g�f�[�^������
			if (typeid(T) == typeid(*(*it))) {
				// ����������R���e�i����폜����
				m_ComponentPool.erase(it);
				// �폜�ł��������Ԃ�
				return true;
			}
		// �폜�ł��Ȃ����������Ԃ�
		return false;
	}
	//--- �����蔻��
	void CallCollisionEnter(ObjectBase* object) {
		for (auto it = m_ComponentPool.begin(); it != m_ComponentPool.end(); ++it)
			(*it)->OnCollisionEnter(object);
	}
	void CallCollisionStay(ObjectBase* object) {
		for (auto it = m_ComponentPool.begin(); it != m_ComponentPool.end(); ++it)
			(*it)->OnCollisionStay(object);
	}
	void CallCollisionExit(ObjectBase* object) {
		for (auto it = m_ComponentPool.begin(); it != m_ComponentPool.end(); ++it)
			(*it)->OnCollisionExit(object);
	}

	//--- �Q�b�g�֐�
	std::string GetName() { return m_name; }
	std::string GetTag() { return m_tag; }
	bool GetDestroy() { return m_isDestroy; }
	std::shared_ptr<ObjectBase> GetParent() { return m_Parent; }
	int GetLayerNum() { return m_LayerNum; }
	std::shared_ptr<ObjectBase> GetThisPtr() { return m_this; }

	//--- �Z�b�g�֐�
	void SetDestroy(bool destroy) { m_isDestroy = destroy; }
	void SetParent(std::shared_ptr<ObjectBase> parent) { m_Parent = parent; }
	void SetLayerNum(int layerNum) { m_LayerNum = layerNum; }

protected:
	// �l�[��
	std::string m_name;
	// �^�O
	std::string m_tag;
	// �폜�t���O
	bool m_isDestroy;

	// �R���|�[�l���g�i�[�v�[��
	ComponentPool m_ComponentPool;
	ComponentPool m_DestroyComponentPool;

	// ���g�̃|�C���^
	std::shared_ptr<ObjectBase> m_this;

	// �e�I�u�W�F�N�g�̃|�C���^
	std::shared_ptr<ObjectBase> m_Parent;

	// ���C���[�ԍ�
	int m_LayerNum;
};

// ���C���[�ԍ��ɂ���r
bool operator<(const std::shared_ptr<ObjectBase>& left, const std::shared_ptr<ObjectBase>& right);
bool operator>(const std::shared_ptr<ObjectBase>& left, const std::shared_ptr<ObjectBase>& right);
#endif //!___OBJECT_H___