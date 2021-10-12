// Fill out your copyright notice in the Description page of Project Settings.


#include "Bat.h"

#include "EnemyBullet.h"
#include "Engine/SkeletalMeshSocket.h"

ABat::ABat()
{
	DelayAttackTime = 3.f;
	BulletSpeed = 1000.f;
}

void ABat::Attack()
{
	// Boss Enemy 소켓 가져오기
	const USkeletalMeshSocket* MuzzleSocket = GetMesh()->GetSocketByName("BatBulletSocket");
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

void ABat::FinishDeath()
{
	Super::FinishDeath();
}
