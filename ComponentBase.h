#ifndef ___COMPONENT_H___
#define ___COMPONENT_H___

#include <memory>

class ObjectBase;
class ComponentBase
{
	friend class ObjectBase;
private:
	// �e�I�u�W�F�N�g
	ObjectBase* m_Owner;
public:
	// �R���X�g���N�^
	ComponentBase();
	// �f�X�g���N�^
	virtual ~ComponentBase() {}

	virtual void Start(){}
	// �O�X�V
	virtual void FixedUpdate() {}
	// �X�V
	virtual void Update() {}
	// ��X�V
	virtual void LateUpdate() {}

	virtual void End(){}

	// �����蔻��
	virtual void OnCollisionEnter(ObjectBase* object){}
	virtual void OnCollisionStay(ObjectBase* object){}
	virtual void OnCollisionExit(ObjectBase* object){}

	// �i�[�I�u�W�F�N�g���擾
	ObjectBase* GetOwner();

	// �i�[�I�u�W�F�N�g���Z�b�g
	void SetOwner(ObjectBase* Owner);
};

#endif //!___COMPONENT_H___