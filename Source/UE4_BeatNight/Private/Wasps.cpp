// Fill out your copyright notice in the Description page of Project Settings.


#include "Wasps.h"

#include "EnemyBullet.h"
#include "Engine/SkeletalMeshSocket.h"


AWasps::AWasps()
{
	DelayAttackTime = 3.f;
	BulletSpeed = 1000.f;
}

void AWasps::Attack()
{
	// Boss Enemy 소켓 가져오기
	const USkeletalMeshSocket* MuzzleSocket = GetMesh()->GetSocketByName("SpineBulletSocket");
	const FTransform SocketTransForm = MuzzleSocket->GetSocketTransform(GetMesh());
	// 스폰
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if(SpawnBullet)
	{
		AEnemyBullet* Bullet = GetWorld()->SpawnActor<AEnemyBullet>(SpawnBullet,
			SocketTransForm.GetLocation(), GetActorRotation(), Params);
		if(Bullet)
		{
			Bullet->SetBulletInfos(this, BulletSpeed);
		}
	}
}

void AWasps::FinishDeath()
{
	Super::FinishDeath();
}
