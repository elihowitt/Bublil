#pragma once

#include "RENDER/core/shader.h"

namespace render
{
	namespace shaders
	{
		class RelativePositionShader : public Shader
		{
		public:
			RelativePositionShader(const std::string& filename);
			~RelativePositionShader();
		
			void update(const ShaderUpdatePack& pack)override;

		protected:
			static const unsigned int NUM_SHADERS = 2;

			enum
			{
				MODEL_U,
				VIEWANDPROJECTION_U,
				SKYCOLOUR_U,

				NUM_UNIFORMS
			};
			GLuint m_shaders[NUM_SHADERS];
			GLuint m_uniforms[NUM_UNIFORMS];
					
		};

	}
}
