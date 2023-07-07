#ifndef ___DEFINE_H___
#define ___DEFINE_H___

namespace nhs
{
	/*�E�@�\�F�Ώۂ̃p�����[�^�𕶎���ɕϊ�������
		���Ғʂ�̋��������Ȃ��ꍇ�� STRINGIZE ���g�p���Ă�������				*/
	#define STRINGIZE_HELPER(x) #x
	#define STRINGIZE(x) STRINGIZE_HELPER(x)

	/*�E�@�\�F�Ώۂ̃g�[�N����A��������
		���Ғʂ�̋��������Ȃ��ꍇ�� CONCAT ���g�p���Ă�������					*/
	#define CONCAT_HELPER(x,y) x##y
	#define CONCAT(x,y) CONCAT_HELPER(x,y)

	/*�E�@�\�F���S��delete����
	�@�@nullptr���ǂ������`�F�b�N���A�K�v�ɉ�����delete����nullptr��������	*/
	template <class T>
	inline void SAFE_DELETE(T*& p) {
		if (p) {
			delete p;
			p = nullptr;
		}
	}
}

#endif //!___DEFINE_H___