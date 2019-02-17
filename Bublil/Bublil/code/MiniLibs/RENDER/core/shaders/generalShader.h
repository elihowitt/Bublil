#pragma once

#include "RENDER/core/shader.h"

namespace render
{
	namespace shaders
	{
		class GeneralShader :
			public Shader
		{
		public:
			GeneralShader(const std::string& filename);
			virtual ~GeneralShader();

			virtual void update(const ShaderUpdatePack& pack)override;

		protected:
			static const unsigned int NUM_SHADERS = 2;

			enum
			{
				MODEL_U,
				VIEWANDPROJECTION_U,
				VIEW_U,
				PROJECTION_U,
				NORMALMAT_U,
				LIGHTVEC_U,
				SKYCOLOUR_U,

				NUM_UNIFORMS
			};

			GLuint m_shaders[NUM_SHADERS];
			GLuint m_uniforms[NUM_UNIFORMS];
		};
	}
}
