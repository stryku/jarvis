#ifndef _VOLUMECHANGER_HPP_
#define _VOLUMECHANGER_HPP_

#include <Worker.hpp>
#include <VolumeChangerResult.hpp>
#include <SimpleXmlParser.hpp>
#include <log.h>

#include <iostream>

#ifdef _WIN32
    #include <Windows.h>
    #include <mmdeviceapi.h>
    #include <endpointvolume.h>
#endif

class VolumeChanger : public Worker
{
private:
    typedef std::shared_ptr<WorkerResult> WorkerResultPtr;

    struct WorkData
    {
        int8_t newVolumePercents;
    }workData;


    void extractWorkData( const char *taskData )
    {
        auto data = SimpleXmlParser::extractChildren( "newvalue", taskData );

        workData.newVolumePercents = static_cast<int8_t>( std::stoi( data ) );
    }

#ifdef _WIN32
    bool ChangeVolume( double nVolume )
    {
        HRESULT hr = NULL;
        double newVolume = nVolume;

        CoInitialize( NULL );
        IMMDeviceEnumerator *deviceEnumerator = NULL;
        hr = CoCreateInstance( __uuidof( MMDeviceEnumerator ), NULL, CLSCTX_INPROC_SERVER,
                               __uuidof( IMMDeviceEnumerator ), (LPVOID *)&deviceEnumerator );
        IMMDevice *defaultDevice = NULL;

        hr = deviceEnumerator->GetDefaultAudioEndpoint( eRender, eConsole, &defaultDevice );
        deviceEnumerator->Release( );
        deviceEnumerator = NULL;

        IAudioEndpointVolume *endpointVolume = NULL;
        hr = defaultDevice->Activate( __uuidof( IAudioEndpointVolume ),
                                      CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume );
        defaultDevice->Release( );
        defaultDevice = NULL;

        hr = endpointVolume->SetMasterVolumeLevelScalar( (float)newVolume, NULL );

        endpointVolume->Release( );

        CoUninitialize( );

        return FALSE;
    }
#endif

#ifndef __linux__

#endif

public:
    VolumeChanger() {}
    ~VolumeChanger() {}

    WorkerResultPtr doWork( const char *data )
    {
        std::string taskData( data );
        extractWorkData( taskData.c_str() );
        TaskResultCode resultCode;

        LOG( "Changing volume to " << static_cast<int>( workData.newVolumePercents ) << "%" );

        auto volumeChanged = ChangeVolume( static_cast<double>( workData.newVolumePercents ) / 100.0 );

        resultCode = ( volumeChanged ? RC_SUCCESS : RC_FAIL );

        return std::make_shared<VolumeChangerResult>( resultCode );
    }
};

#endif