namespace mb
{
	namespace visitor
	{
		class RayTracerVisitor: public Visitor
		{
		public:
		struct Result
		{
			float t;
			NodePtr node;
		}
		public:
			RayTracerVisitor( mb::Ray& ray,
				const float& tMin = 1e-06, 
				const float& tMax = 
					std::numeric_limits< float >::max( ) )
			: Visitor( )
			, _ray ( ray )
			, _tMin( tMin )
			, _tMax( tMax )
			{
			}
			bool hasMatches( void ) const
			{
				return !_candidates.empty( );
			}

			const Result& bestMatch( void )
			{
				// TODO (getMinDistance instead of sort results??)
				_candidates.sort( []( const Result& rs1, const Result& rs2) 
				{
					return rs1.t < rs2.t;
				});
				return _candidates.front( );
			}

		protected:
			mb::Ray _ray;
			std::vector< Result > _candidates;
			float _tMin;
			float _tMax;
		}
	}
}