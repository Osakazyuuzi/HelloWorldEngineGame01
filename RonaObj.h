#ifndef ___RONA_OBJ_H___
#define ___RONA_OBJ_H___

#include <cstdint>

//-------------------
// �I�u�W�F�N�g
//-------------------
// ��ށF�L�����N�^�[
// �������i�{�X�j
// ���O�F���i
// �N��F�H�H�H�i0�΁j
// ���i�F�H�H�H�i�����R�ƌĂ΂�鎩���B������Ȃ������Ă���B�j
// �R���v���b�N�X�F�H�H�H
// �e�p�F�̂����F�ŁA�Ԃ��p�������Ă���B
// �ړI�F���̐��̒��Ɏ��������i�����R�j�̋��ꏊ��n�낤�Ƃ��Ă���B
// ���Z�F�H�H�H
class RonaObj {
public:
	// �R���X�g���N�^
	RonaObj();
	// �f�X�g���N�^
	~RonaObj();

	// �L�����N�^�[�̃T�C�Y
	constexpr static float mc_sizeX = 1.0f;
	constexpr static float mc_sizeY = 1.5f;
	constexpr static float mc_sizeZ = 1.0f;

	// �o�ꎞ�̃X�e�[�^�X
	constexpr static uint8_t mc_nInitLevel = 1;
	constexpr static uint8_t mc_nInitExperienceMax = 12;
	constexpr static uint8_t mc_nInitAttack = 2;
	constexpr static uint8_t mc_nInitDefense = 2;
	constexpr static uint8_t mc_nInitSpeed = 2;
	constexpr static uint8_t mc_nInitMpMax = 1;
	constexpr static int16_t mc_nInitHpMax = 3;
};

#endif //!___RONA_OBJ_H___