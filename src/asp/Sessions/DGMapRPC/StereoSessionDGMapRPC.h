// __BEGIN_LICENSE__
//  Copyright (c) 2009-2013, United States Government as represented by the
//  Administrator of the National Aeronautics and Space Administration. All
//  rights reserved.
//
//  The NGT platform is licensed under the Apache License, Version 2.0 (the
//  "License"); you may not use this file except in compliance with the
//  License. You may obtain a copy of the License at
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
// __END_LICENSE__


/// \file StereoSessionDGMapRPC.h
///
/// This a session that support RPC Mapproject DG images. It is built
/// entirely so that left and right TX are objects and not TransformRefs.

#ifndef __STEREO_SESSION_DGMAPRPC_H__
#define __STEREO_SESSION_DGMAPRPC_H__

//#include <asp/Sessions/DG/StereoSessionDG.h>
#include <asp/Sessions/StereoSessionConcrete.h>
#include <vw/Cartography/Map2CamTrans.h>
#include <vw/Image/Transform.h>

namespace asp {
 
  
  /*TODO:
     This class has a lot of code dedicated to handling alignment + map projection, but we don't even allow
     alignment with map projected images! (The map projection should take care of the alignment)
     
     All this extra handling is not needed and we can greatly simplify this class without
     losing any functionality.
  */
  
  //class RPCModel; 
  
  
  /// Specialization of the StereoSessionDG class to use map-projected inputs with the RPC sensor model.
  class StereoSessionDGMapRPC : public StereoSessionConcrete<DISKTRANSFORM_TYPE_MAP_PROJECT, STEREOMODEL_TYPE_DG> {//StereoSessionDG {
  public:
    StereoSessionDGMapRPC(){};
    virtual ~StereoSessionDGMapRPC(){};

    /*
    /// Initializer verifies that the input is map projected
    virtual void initialize(BaseOptions const& options,
                            std::string const& left_image_file,
                            std::string const& right_image_file,
                            std::string const& left_camera_file,
                            std::string const& right_camera_file,
                            std::string const& out_prefix,
                            std::string const& input_dem);
*/
    virtual std::string name() const { return "dgmaprpc"; }

    /// Disable this function 
    /// - IP matching is not needed because alignment is not supported for map projected images!
    virtual bool ip_matching(std::string const& input_file1,
                             std::string const& input_file2,
                             float nodata1, float nodata2,
                             std::string const& match_filename,
                             vw::camera::CameraModel* cam1,
                             vw::camera::CameraModel* cam2);
/*
    /// Transforms from pixel coordinates on disk to original unwarped image coordinates.
    /// - For reversing the arithmetic applied in preprocessing plus the map projection.
    /// - This combines the homography/affineEpipolar transform with the map-to-camera transform
    ///   so that we can recover the original image pixels from a warped map projected image.
    typedef vw::cartography::Map2CamTrans tx_type;
    typedef vw::stereo::StereoModel       stereo_model_type;
    tx_type tx_left () const;
    tx_type tx_right() const;
*/
    static StereoSession* construct() { return new StereoSessionDGMapRPC; }
/*
    // TODO: Why is this public?
    /// RPC camera models used only in the tx_left and tx_right functions.
    /// - Read in initialize()
    boost::shared_ptr<RPCModel> m_left_model, m_right_model;
*/
  };

}

#endif//__STEREO_SESSION_DGMAPRPC_H__
