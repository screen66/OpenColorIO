/*
Copyright (c) 2003-2010 Sony Pictures Imageworks Inc., et al.
All Rights Reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:
* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
* Neither the name of Sony Pictures Imageworks nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <iostream>

#include <OpenColorIO/OpenColorIO.h>

#include "OpBuilders.h"
#include "TruelightOp.h"
#include "pystring/pystring.h"

OCIO_NAMESPACE_ENTER
{
    
    TruelightTransformRcPtr TruelightTransform::Create()
    {
        return TruelightTransformRcPtr(new TruelightTransform(), &deleter);
    }
    
    void TruelightTransform::deleter(TruelightTransform* t)
    {
        delete t;
    }
    
    class TruelightTransform::Impl
    {
    public:
        TransformDirection dir_;
        std::string configroot_;
        std::string profile_;
        std::string camera_;
        std::string inputdisplay_;
        std::string recorder_;
        std::string print_;
        std::string lamp_;
        std::string outputcamera_;
        std::string display_;
        std::string cubeinput_;
        
        Impl() : dir_(TRANSFORM_DIR_FORWARD)
        { }
        
        ~Impl()
        { }
        
        Impl& operator= (const Impl & rhs)
        {
            dir_ = rhs.dir_;
            configroot_ = rhs.configroot_;
            profile_ = rhs.profile_;
            camera_ = rhs.camera_;
            inputdisplay_ = rhs.inputdisplay_;
            recorder_ = rhs.recorder_;
            print_ = rhs.print_;
            lamp_ = rhs.lamp_;
            outputcamera_ = rhs.outputcamera_;
            display_ = rhs.display_;
            cubeinput_ = rhs.cubeinput_;
            return *this;
        }
    };
    
    ///////////////////////////////////////////////////////////////////////////
    
    TruelightTransform::TruelightTransform()
        : m_impl(new TruelightTransform::Impl)
    {
        getImpl()->configroot_ = "/usr/fl/truelight";
        getImpl()->profile_ = "";
        getImpl()->camera_ = "";
        getImpl()->inputdisplay_ = "";
        getImpl()->recorder_ = "";
        getImpl()->print_ = "";
        getImpl()->lamp_ = "";
        getImpl()->outputcamera_ = "";
        getImpl()->display_ = "";
        getImpl()->cubeinput_ = "log";
    }
    
    TransformRcPtr TruelightTransform::createEditableCopy() const
    {
        TruelightTransformRcPtr transform = TruelightTransform::Create();
        *(transform->m_impl) = *m_impl;
        return transform;
    }
    
    TruelightTransform::~TruelightTransform()
    {
        delete m_impl;
        m_impl = NULL;
    }
    
    TruelightTransform& TruelightTransform::operator= (const TruelightTransform & rhs)
    {
        *m_impl = *rhs.m_impl;
        return *this;
    }
    
    TransformDirection TruelightTransform::getDirection() const
    {
        return getImpl()->dir_;
    }
    
    void TruelightTransform::setDirection(TransformDirection dir)
    {
        getImpl()->dir_ = dir;
    }
    
    void TruelightTransform::setConfigRoot(const char * configroot)
    {
        getImpl()->configroot_ = configroot;
    }
    
    const char * TruelightTransform::getConfigRoot() const
    {
        return getImpl()->configroot_.c_str();
    }
    
    void TruelightTransform::setProfile(const char * profile)
    {
        getImpl()->profile_ = profile;
    }
    
    const char * TruelightTransform::getProfile() const
    {
        return getImpl()->profile_.c_str();
    }
    
    void TruelightTransform::setCamera(const char * camera)
    {
        getImpl()->camera_ = camera;
    }
    
    const char * TruelightTransform::getCamera() const
    {
        return getImpl()->camera_.c_str();
    }
    
    void TruelightTransform::setInputDisplay(const char * display)
    {
        getImpl()->inputdisplay_ = display;
    }
    
    const char * TruelightTransform::getInputDisplay() const
    {
        return getImpl()->inputdisplay_.c_str();
    }
    
    void TruelightTransform::setRecorder(const char * recorder)
    {
        getImpl()->recorder_ = recorder;
    }
    
    const char * TruelightTransform::getRecorder() const
    {
        return getImpl()->recorder_.c_str();
    }
    
    void TruelightTransform::setPrint(const char * print)
    {
        getImpl()->print_ = print;
    }
    
    const char * TruelightTransform::getPrint() const
    {
        return getImpl()->print_.c_str();
    }
    
    void TruelightTransform::setLamp(const char * lamp)
    {
        getImpl()->lamp_ = lamp;
    }
    
    const char * TruelightTransform::getLamp() const
    {
        return getImpl()->lamp_.c_str();
    }
    
    void TruelightTransform::setOutputCamera(const char * camera)
    {
        getImpl()->outputcamera_ = camera;
    }
    
    const char * TruelightTransform::getOutputCamera() const
    {
        return getImpl()->outputcamera_.c_str();
    }
    
    void TruelightTransform::setDisplay(const char * display)
    {
        getImpl()->display_ = display;
    }
    
    const char * TruelightTransform::getDisplay() const
    {
        return getImpl()->display_.c_str();
    }
    
    void TruelightTransform::setCubeInput(const char * cubeinput)
    {
        getImpl()->cubeinput_ = pystring::lower(cubeinput);
    }
    
    const char * TruelightTransform::getCubeInput() const
    {
        return getImpl()->cubeinput_.c_str();
    }
    
    std::ostream& operator<< (std::ostream& os, const TruelightTransform& t)
    {
        os << "<TruelightTransform ";
        os << "direction=" << TransformDirectionToString(t.getDirection()) << ", ";
        os << ">\n";
        return os;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    
    void BuildTruelightOps(OpRcPtrVec & ops,
                           const Config& /*config*/,
                           const TruelightTransform & transform,
                           TransformDirection dir)
    {
        TransformDirection combinedDir = CombineTransformDirections(dir,
            transform.getDirection());
        
        #ifndef _TRUELIGHT_
        // TODO: throw exception if we didn't build with truelight support
        #endif // _TRUELIGHT_
        
        CreateTruelightOps(ops, transform, combinedDir);
        
    }
    
}
OCIO_NAMESPACE_EXIT

///////////////////////////////////////////////////////////////////////////////

#ifdef OCIO_UNIT_TEST

namespace OCIO = OCIO_NAMESPACE;
#include "UnitTest.h"

BOOST_AUTO_TEST_SUITE( Truelight_Unit_Tests )

BOOST_AUTO_TEST_CASE ( test_simpletest )
{
    
    OCIO::ConfigRcPtr config = OCIO::Config::Create();
    {
        OCIO::ColorSpaceRcPtr cs = OCIO::ColorSpace::Create();
        cs->setName("log");
        cs->setFamily("log");
        config->addColorSpace(cs);
        config->setRole(OCIO::ROLE_COMPOSITING_LOG, cs->getName());
    }
    {
        OCIO::ColorSpaceRcPtr cs = OCIO::ColorSpace::Create();
        cs->setName("sRGB");
        cs->setFamily("srgb");
        OCIO::TruelightTransformRcPtr transform1 = OCIO::TruelightTransform::Create();
        transform1->setConfigRoot("/usr/fl/truelight");
        transform1->setPrint("internal-LowContrast");
        //transform1->setInputDisplay("DCIrgb");
        transform1->setDisplay("sRGB");
        transform1->setCubeInput("log");
        cs->setTransform(transform1, OCIO::COLORSPACE_DIR_FROM_REFERENCE);
        config->addColorSpace(cs);
    }
    
    // check the transform round trip
    OCIO::ConstProcessorRcPtr tosrgb;
    OCIO::ConstProcessorRcPtr tolog;
    
#ifdef OCIO_TRUELIGHT_SUPPORT
    BOOST_CHECK_NO_THROW(tosrgb = config->getProcessor("log", "sRGB"));
    BOOST_CHECK_NO_THROW(tolog = config->getProcessor("sRGB", "log"));
#else
    BOOST_CHECK_THROW(tosrgb = config->getProcessor("log", "sRGB"), OCIO::Exception);
    BOOST_CHECK_THROW(tolog = config->getProcessor("sRGB", "log"), OCIO::Exception);
#endif
    
    float input[3] = {0.5f, 0.5f, 0.5f};
    float output[3] = {0.500098f, 0.500317f, 0.501134f};
    
#ifdef OCIO_TRUELIGHT_SUPPORT
    BOOST_CHECK_NO_THROW(tosrgb->applyRGB(input));
    BOOST_CHECK_NO_THROW(tolog->applyRGB(input));
    BOOST_CHECK_CLOSE(input[0], output[0], 1e-4);
    BOOST_CHECK_CLOSE(input[1], output[1], 1e-4);
    BOOST_CHECK_CLOSE(input[2], output[2], 1e-4);
#endif
    
    //
    std::ostringstream os;
    BOOST_CHECK_NO_THROW(config->serialize(os));
    
    std::string testconfig =
    "---\n"
    "ocio_profile_version: 1\n"
    "\n"
    "search_path: \"\"\n"
    "strictparsing: true\n"
    "luma: [0.2126, 0.7152, 0.0722]\n"
    "\n"
    "roles:\n"
    "  compositing_log: log\n"
    "\n"
    "displays:\n"
    "  {}\n"
    "active_displays: []\n"
    "active_views: []\n"
    "\n"
    "colorspaces:\n"
    "  - !<ColorSpace>\n"
    "    name: log\n"
    "    family: log\n"
    "    bitdepth: unknown\n"
    "    isdata: false\n"
    "    allocation: uniform\n"
    "\n"
    "  - !<ColorSpace>\n"
    "    name: sRGB\n"
    "    family: srgb\n"
    "    bitdepth: unknown\n"
    "    isdata: false\n"
    "    allocation: uniform\n"
    "    from_reference: !<TruelightTransform> {config_root: /usr/fl/truelight, print: internal-LowContrast, display: sRGB, cube_input: log}\n";
    
    std::vector<std::string> osvec;
    OCIO::pystring::splitlines(os.str(), osvec);
    std::vector<std::string> testconfigvec;
    OCIO::pystring::splitlines(testconfig, testconfigvec);
    
    BOOST_CHECK_EQUAL(osvec.size(), testconfigvec.size());
    for(unsigned int i = 0; i < testconfigvec.size(); ++i)
        BOOST_CHECK_EQUAL(osvec[i], testconfigvec[i]);
    
    std::istringstream is;
    is.str(testconfig);
    OCIO::ConstConfigRcPtr rtconfig;
    BOOST_CHECK_NO_THROW(rtconfig = OCIO::Config::CreateFromStream(is));
    
}

BOOST_AUTO_TEST_SUITE_END()

#endif // OCIO_BUILD_TESTS