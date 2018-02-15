#pragma once
#include "IGameObject.h"
class SceneChange :
	public IGameObject
{
public:

	//デストラクタ
	~SceneChange();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	//void Draw();

	int GetMapNo()
	{
		return m_stageNo;
	}

	void SetMapNo(int No)
	{
		m_stageNo = No;
	}

	void SetChange(bool Change)
	{
		m_isChange = Change;
	}

	bool GetChange()
	{
		return m_isChange;
	}
	//インスタンスの取得
	static SceneChange& GetInstance()
	{
		return *m_change;
	}
	//インスタンスの生成
	static void SceneChange::Create()
	{
		if (!m_change)
		{
			m_change = new SceneChange;
		}

	}
	//インスタンスの消去
	static  void SceneChange::Destroy()
	{
		delete m_change;
		m_change = nullptr;
	}
private:

	//コンストラクタ
	SceneChange();
	static SceneChange* m_change;//インスタンス
	int m_stageNo = 0;
	bool m_isChange=false;
};

