#pragma once
#include "Util.h"

class NameKey {
	std::string name;			//!<���O
	unsigned int hashCode = 0;	//!<�n�b�V���l�B
public:
	NameKey() {}
	NameKey(const char* name)
	{
		Init(name);
	}
	//�������B
	void Init(const char* name)
	{
		if (name != nullptr) {
			this->name = name;
			//���O���n�b�V���l�ɕϊ��B
			hashCode = CUtil::MakeHash(name);
		}
	}
	//�n�b�V���R�[�h���擾�B
	unsigned int GetHashCode() const
	{
		return hashCode;
	}
	//���O���擾�B
	const char* GetName() const
	{
		return name.c_str();
	}
};