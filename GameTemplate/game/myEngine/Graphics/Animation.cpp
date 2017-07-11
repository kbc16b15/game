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
	//�A�j���[�V�����Z�b�g���������B
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
			//0�ԖڈȊO�̃g���b�N�͖����ɂ���B
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
		//�A�j���[�V�����̃C���f�b�N�X���s���ł��B
		std::abort();
	}
}
void Animation::PlayAnimation(int animationSetIndex, float interpolateTime)
{
	if (animationSetIndex < numAnimSet) {
		if (pAnimController) {
			//��ԊJ�n�̈�B
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
		//�A�j���[�V�����̃C���f�b�N�X���s���ł��B
		std::abort();
	}
}
void Animation::Update(float deltaTime)
{
	if (pAnimController) {
		localAnimationTime += deltaTime;
		
		if (animationEndTime[currentAnimationSetNo] > 0.0 //�A�j���[�V�����̏I�����Ԃ��ݒ肳��Ă���B
			&& localAnimationTime > animationEndTime[currentAnimationSetNo] //�A�j���[�V�����̏I�����Ԃ𒴂����B
		) {
			localAnimationTime -= animationEndTime[currentAnimationSetNo];
			pAnimController->SetTrackPosition(currentTrackNo, localAnimationTime);
			pAnimController->AdvanceTime(0, NULL);
		}
		else {
			//���ʂɍĐ��B
			pAnimController->AdvanceTime(deltaTime, NULL);
		}
		if (isInterpolate) {
			ID3DXAnimationSet* animSet = animationSets[2];
			float period = (float)animSet->GetPeriod();
			//��Ԓ��B
			interpolateTime += deltaTime;
			float weight = 0.0f;
			if (interpolateTime > interpolateEndTime) {
				//��ԏI���B
				isInterpolate = false;
				weight = 1.0f;
				//���݂̃g���b�N�ȊO�𖳌��ɂ���B
				for (int i = 0; i < numMaxTracks; i++) {
					if (i != currentTrackNo) {
						pAnimController->SetTrackEnable(i, FALSE);
					}
				}
			}
			else {
				weight = interpolateTime / interpolateEndTime;
				float invWeight = 1.0f - weight;
				//�E�F�C�g��ݒ肵�Ă����B
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
