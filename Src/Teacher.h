//����� ������������ ����� ��������� 21317��  
// ����� �������

#pragma once

#include "Entity.hpp"

class CTeacher : public CEntity {
public:
	int direction1;//����������� �������� �����

	CTeacher();             // ������������ � ��� ��������� � � ����������� 
	CTeacher(sf::Texture&, float, float, int, int, std::string);
//	~CEnemy();

	void CollisionWithMap(float m_fDx, float m_fDy);//�-��� �������� ������������ � ������
	void Frame(float& fTime);

	std::string* m_pszMapCode;
	void setMap(std::string* dsd) {m_pszMapCode = dsd;}

	sf::Sprite getSprite() {return m_Sprite;}

};
