#include "stdafx.h"
#include "myEngine/Graphics/Animation.h"

void Animation::Init(ID3DXAnimationController* anim)
{
	pAnimController = anim;
	ID3DXAnimationSet* animSet;
	pAnimController->GetAnimationSet(0, &animSet);
	numAnimSet = pAnimController->GetMaxNumAnimationSets();
	numMaxTracks = pAnimController->GetMaxNumTracks();
	blendRateTable.reset( new float[numMaxTracks] );
	animationEndTime.reset(new double[numAnimSet]);
	animationSets.reset(new ID3DXAnimationSet*[numAnimSet]);
	for( int i = 0; i < numMaxTracks; i++ ){
		blendRateTable[i] = 1.0f;
	}
	//アニメーションセットを初期化。
	for (int i = 0; i < numAnimSet; i++) {
		pAnimController->GetAnimationSet(i, &animationSets[i]);
		animationEndTime[i] = -1.0;
	}
	localAnimationTime = 0.0;
}

void Animation::PlayAnimation(int animationSetIndex)
{
	if (animationSetIndex < numAnimSet) {
		if (pAnimController) {
			currentAnimationSetNo = animationSetIndex;
			currentTrackNo = 0;
			//0番目以外のトラックは無効にする。
			for (int i = 1; i < numMaxTracks; i++) {
				pAnimController->SetTrackEnable(i,  FALSE);
			}
			pAnimController->SetTrackWeight(0, 1.0f);
			pAnimController->SetTrackAnimationSet(currentTrackNo, animationSets[currentAnimationSetNo]);
			pAnimController->SetTrackEnable(0, TRUE);
			pAnimController->SetTrackPosition(0, 0.0f);
			localAnimationTime = 0.0;
		}
	}
	else {
		//アニメーションのインデックスが不正です。
		std::abort();
	}
}
void Animation::PlayAnimation(int animationSetIndex, float interpolateTime)
{
	if (animationSetIndex < numAnimSet) {
		if (pAnimController) {
			//補間開始の印。
			isInterpolate = true;
			this->interpolateTime = 0.0f;
			interpolateEndTime = interpolateTime;
			currentTrackNo = (currentTrackNo+1) % numMaxTracks;
			pAnimController->SetTrackAnimationSet( currentTrackNo, animationSets[animationSetIndex]);
			pAnimController->SetTrackEnable(currentTrackNo, TRUE);
			pAnimController->SetTrackSpeed(currentTrackNo, 1.0f);
			pAnimController->SetTrackPosition(currentTrackNo, 0.0f);
			localAnimationTime = 0.0;
			currentAnimationSetNo = animationSetIndex;
		}
	}
	else {
		//アニメーションのインデックスが不正です。
		std::abort();
	}
}
void Animation::Update(float deltaTime)
{
	if (pAnimController) {
		localAnimationTime += deltaTime;
		
		if (animationEndTime[currentAnimationSetNo] > 0.0 //アニメーションの終了時間が設定されている。
			&& localAnimationTime > animationEndTime[currentAnimationSetNo] //アニメーションの終了時間を超えた。
		) {
			localAnimationTime -= animationEndTime[currentAnimationSetNo];
			pAnimController->SetTrackPosition(currentTrackNo, localAnimationTime);
			pAnimController->AdvanceTime(0, NULL);
		}
		else {
			//普通に再生。
			pAnimController->AdvanceTime(deltaTime, NULL);
		}
		if (isInterpolate) {
			ID3DXAnimationSet* animSet = animationSets[2];
			float period = (float)animSet->GetPeriod();
			//補間中。
			interpolateTime += deltaTime;
			float weight = 0.0f;
			if (interpolateTime > interpolateEndTime) {
				//補間終了。
				isInterpolate = false;
				weight = 1.0f;
				//現在のトラック以外を無効にする。
				for (int i = 0; i < numMaxTracks; i++) {
					if (i != currentTrackNo) {
						pAnimController->SetTrackEnable(i, FALSE);
					}
				}
			}
			else {
				weight = interpolateTime / interpolateEndTime;
				float invWeight = 1.0f - weight;
				//ウェイトを設定していく。
				for (int i = 0; i < numMaxTracks; i++) {
					if (i != currentTrackNo) {
						pAnimController->SetTrackWeight(i, blendRateTable[i] * invWeight);
					}
					else {
						pAnimController->SetTrackWeight(i, weight);
					}
				}
			}
		}
	}
}
