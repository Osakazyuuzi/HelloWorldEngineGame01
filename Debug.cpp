#include "Debug.h"
#include <Windows.h>
#include <string>

/*�E�@�\�F�f�o�b�K�ɕ�������o��
�@�@�f�o�b�O�o�̓E�B���h�E�ɕ�����𒼐ڑ��M����							*/
void nhs::DebugLog(const char* format, ...)
{
#ifdef _DEBUG

	//--- �ϐ��錾
	char buf[1024];		//�o�b�t�@
	va_list ap;			//�ϒ��𑀍삷��ׂ̍\����
	int resultNum = 0;	//�������ʂ̐��l���i�[

	va_start(ap, format);	//�ϒ������̑�����J�n

	resultNum = vsprintf_s(buf, format, ap);

	//--- �G���[���o����
	if (resultNum < 0)
	{
		OutputDebugString("\nLog output failed");	//�G���[���b�Z�[�W���o��

		//--- �I������
		va_end(ap);		//�ϒ������̑�����I��
		return;			//�����I��
	}

	OutputDebugString(buf);		//�w�肳�ꂽ��������o��

	va_end(ap);	//�ϒ������̑�����I��
#endif //_DEBUG
}