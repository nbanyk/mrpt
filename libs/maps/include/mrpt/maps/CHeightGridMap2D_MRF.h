/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2016, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+ */

#ifndef CHeightGridMap2D_MRF_MRF_H
#define CHeightGridMap2D_MRF_MRF_H

#include <mrpt/maps/CRandomFieldGridMap2D.h>
#include <mrpt/maps/link_pragmas.h>

namespace mrpt
{
namespace maps
{
	DEFINE_SERIALIZABLE_PRE_CUSTOM_BASE_LINKAGE( CHeightGridMap2D_MRF , CRandomFieldGridMap2D, MAPS_IMPEXP )

	/** CHeightGridMap2D_MRF represents a PDF of gas concentrations over a 2D area
	  *
	  *  There are a number of methods available to build the gas grid-map, depending on the value of
	  *    "TMapRepresentation maptype" passed in the constructor (see base class mrpt::maps::CRandomFieldGridMap2D).
	  *
	  * Update the map with insertIndividualReading() or insertObservation()
	  *
	  * \sa mrpt::maps::CRandomFieldGridMap2D, mrpt::maps::CMetricMap, mrpt::utils::CDynamicGrid, The application icp-slam, mrpt::maps::CMultiMetricMap
	  * \ingroup mrpt_maps_grp
	  */
	class MAPS_IMPEXP CHeightGridMap2D_MRF : public CRandomFieldGridMap2D
	{
		// This must be added to any CSerializable derived class:
		DEFINE_SERIALIZABLE( CHeightGridMap2D_MRF )
	public:
		/** Constructor */
		CHeightGridMap2D_MRF(
			TMapRepresentation	mapType = mrGMRF_SD,
			double x_min = -2, double x_max = 2,
			double y_min = -2, double y_max = 2, double resolution = 0.1,
			bool  run_first_map_estimation_now=true  //!< [in] Whether to call updateMapEstimation(). If false, make sure of calling that function before accessing map contents.
			);

		virtual ~CHeightGridMap2D_MRF(); //!< Destructor

		/** Parameters related with inserting observations into the map */
		struct MAPS_IMPEXP TInsertionOptions :
			public utils::CLoadableOptions,
			public TInsertionOptionsCommon
		{
			TInsertionOptions();	//!< Default values loader

			void loadFromConfigFile(const mrpt::utils::CConfigFileBase &source,const std::string &section) MRPT_OVERRIDE; // See base docs
			void dumpToTextStream(mrpt::utils::CStream &out) const MRPT_OVERRIDE; // See base docs
		} insertionOptions;

		/** Returns a 3D object representing the map */
		virtual void getAs3DObject( mrpt::opengl::CSetOfObjectsPtr &outObj ) const MRPT_OVERRIDE;

		/** Returns two 3D objects representing the mean and variance maps */
		virtual void  getAs3DObject ( mrpt::opengl::CSetOfObjectsPtr	&meanObj, mrpt::opengl::CSetOfObjectsPtr	&varObj ) const MRPT_OVERRIDE;

	protected:
		/** Get the part of the options common to all CRandomFieldGridMap2D classes */
		virtual CRandomFieldGridMap2D::TInsertionOptionsCommon * getCommonInsertOptions()  MRPT_OVERRIDE {
			return &insertionOptions;
		}

		// See docs in base class
		void  internal_clear() MRPT_OVERRIDE;
		bool  internal_insertObservation( const mrpt::obs::CObservation *obs, const mrpt::poses::CPose3D *robotPose = NULL ) MRPT_OVERRIDE;
		double internal_computeObservationLikelihood( const mrpt::obs::CObservation *obs, const mrpt::poses::CPose3D &takenFrom ) MRPT_OVERRIDE;

		MAP_DEFINITION_START(CHeightGridMap2D_MRF,MAPS_IMPEXP)
			bool    run_map_estimation_at_ctor;  //!< Runs map estimation at start up (Default:true)
			double  min_x,max_x,min_y,max_y,resolution;	//!< See CHeightGridMap2D_MRF::CHeightGridMap2D_MRF
			mrpt::maps::CHeightGridMap2D_MRF::TMapRepresentation  mapType;	//!< The kind of map representation (see CHeightGridMap2D_MRF::CHeightGridMap2D_MRF)
			mrpt::maps::CHeightGridMap2D_MRF::TInsertionOptions   insertionOpts;	//!< Observations insertion options
		MAP_DEFINITION_END(CHeightGridMap2D_MRF,MAPS_IMPEXP)
	};

	DEFINE_SERIALIZABLE_POST_CUSTOM_BASE_LINKAGE( CHeightGridMap2D_MRF , CRandomFieldGridMap2D, MAPS_IMPEXP )

	} // End of namespace
} // End of namespace
#endif
