#ifndef _VOLUMECHANGER_HPP_
#define _VOLUMECHANGER_HPP_

#include "Worker.hpp"
#include "VolumeChangerResult.hpp"
#include "SimpleXmlParser.hpp"
#include "log.h"

#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#endif

#ifdef __linux__
#include <alsa/asoundlib.h>
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

#ifdef __linux__
        bool ChangeVolume( double volume )
        {
            long min, max;
            snd_mixer_t *handle;
            snd_mixer_selem_id_t *sid;
            const char *card = "default";
            const char *selem_name = "Master";

            snd_mixer_open(&handle, 0);
            snd_mixer_attach(handle, card);
            snd_mixer_selem_register(handle, NULL, NULL);
            snd_mixer_load(handle);

            snd_mixer_selem_id_alloca(&sid);
            snd_mixer_selem_id_set_index(sid, 0);
            snd_mixer_selem_id_set_name(sid, selem_name);
            snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

            snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
            snd_mixer_selem_set_playback_volume_all(elem, volume * max / 100);

            snd_mixer_close(handle);

            return true;
        }
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
