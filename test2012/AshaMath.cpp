//AshaMath.cpp
#include "AshaMath.h"


aMath::aMat aMath::getProjMat(float fovyrad,float aspect,float znear,float zfar )
{
	return XMMatrixPerspectiveFovLH(fovyrad,aspect,znear,zfar);

	//xScale     0          0               0
    //0        yScale       0               0
    //0          0       zf/(zf-zn)         1
    //0          0       -zn*zf/(zf-zn)     0
    //where:
    //yScale = cot(fovY/2)
    //xScale = yScale / aspect ratio
}

//unit matrix
aMath::aMat aMath::getWorldMat()
{
	return XMMatrixIdentity();
}

//left-handed orthographic projection matrix
aMath::aMat aMath::getOrthMat(float wide,float height,float znear,float zfar)
{
	return XMMatrixOrthographicLH(wide,height,znear,zfar);

	//2/w  0    0           0
    //0    2/h  0           0
    //0    0    1/(zf-zn)   0
    //0    0   -zn/(zf-zn)  1
  
}

aMath::aMat aMath::getAixRotaMat(float roateAix[4],float angleRad)
{
	return XMMatrixRotationNormal(arry2xmvec(roateAix),angleRad);

}

aMath::aMat aMath::getCameraMat(float eyePos[4],float objPos[4],float upPos[4])
{
	return XMMatrixLookAtLH(arry2xmvec(eyePos),arry2xmvec(objPos),arry2xmvec(upPos));
}

XMVECTOR aMath::arry2xmvec(float srcArray[4])
{
	XMVECTOR vecbuff;
	for(int i=0;i<4;i++)
	{
		vecbuff.m128_f32[i]=srcArray[i];
	}

	return vecbuff;
}
