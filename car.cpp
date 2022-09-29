#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	//�҂�����
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 180;
	//�Ԃ̍s������Y���W
	constexpr int kMoob = 384;
	//�Ԃ̑��x
	constexpr float kSpeed = -24.0f;
	//�W�����v��
	constexpr float kJumpAcc = -21.0f;
	//�d��
	constexpr float kGravity = 1.0f;
}

Car::Car()
{
	m_handle = -1;
	m_fieldY = 0.0f;
	m_waitFrame = 0;
}

void Car::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_size.x, &m_size.y);
}

void Car::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = Game::kScreenWidth + 16.0f;
	m_pos.y = m_fieldY - m_size.y;

	m_vec.x = -16.0f;
	m_vec.y = 0.0f;


	//�����̃o���G�[�V������I��
	int randNum = GetRand(99);
	if (randNum < 38) {
		m_moveType = kMoveTypeNormal;
	}
	else if (randNum < 38+30) {
		m_moveType = kMoveTypeStop;
	}
	else if (randNum < 38 + 30+30) {
		m_moveType = kMoveTypeJump;
	}
	else{
		m_moveType = kMoveTypeReturn;
	}
	m_moveType = kMoveTypeReturn;

	//�����n�߂�܂ł̎��Ԃ�ݒ�	��b����O�b�҂�	60�t���[������180�t���[��
	m_waitFrame=GetRand(kWaitFrameMax -kWaitFrameMin)+ kWaitFrameMin;
}

void Car::update()
{
	if (m_waitFrame > 0) {
		m_waitFrame--;
		return;
	}
	switch (m_moveType)
	{
	case kMoveTypeNormal:
		updateNormal();
		break;
	case kMoveTypeStop:
			updateStop();
			break;
	case kMoveTypeJump:
			updateJump();
			break;
	case kMoveTypeReturn:
			updateReturn();
			break;
	}
}

void Car::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}

//�܂������i��
void Car::updateNormal()
{
	m_pos += m_vec;
}

//�ꎞ��~�t�F�C���g
void Car::updateStop()
{
	;
}

//�W�����v����
void Car::updateJump()
{
	m_pos += m_vec;
	//�n�ʂƂ̓�����
	bool isField = false;
	if (m_pos.y > m_fieldY - m_size.y) {
		m_pos.y = m_fieldY - m_size.y;
		isField = true;
	}

	if (m_pos.x == kMoob)
	{
		if (isField) {
			m_vec.y = kJumpAcc;	//�W�����v�J�n
		}
	}
	m_vec.y += kGravity;
}

//�r���ň����Ԃ�(�K������)
void Car::updateReturn()
{
	m_pos += m_vec;
	if (m_pos.x == kMoob)
	{
		m_pos -= m_vec;

	}
}