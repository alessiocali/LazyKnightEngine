#pragma once
#include <lazye/lazye.h>

#include <lazye/math/matrix.h>

namespace lazye
{
    class lazyedll Camera
    {
    public:
        enum class Type
        {
            Orthogonal,
            Perspective
        };

        /**
         *  Parameters defining a symmetric Frustum.
         *
         *  @param m_FoV:   Full Horizontal Field of View (in Radians). 
         *                  Must be positive and less than 180 Degrees.
         *  @param m_Ratio: Ratio between the view's width and height.
         *  @param m_Near:  Near plane position. Must be positive.
         *  @param m_Far:   Far plane position. Must be greater than m_Near.
         */
        struct FrustumParameters
        {
            Radians m_FoV;
            float m_Ratio;
            float m_Near;
            float m_Far;
        };

        Camera(const FrustumParameters& params, const Type type);

        inline const Matrix44f& GetProjectionMatrix() const { return m_Matrix; }

    private:

        static void SetToOrthogonalProjectionMatrix(Matrix44f& matrix, const FrustumParameters& params);
        static void SetToPerspectiveProjectionMatrix(Matrix44f& matrix, const FrustumParameters& params);

        Matrix44f m_Matrix;
    };
}