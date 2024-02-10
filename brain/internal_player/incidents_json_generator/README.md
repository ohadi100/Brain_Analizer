Setup:
---------------------------------------------

In order to use this utility one needs to have templates of incidents, and python 3 installed.


End to end flow:
---------------------------------------------

The general idea is to first generate a JSON file that will contain all the incidents in advance with special time stamp offsets, and then run the brain with the "InternalPlayer" enabled, which will load the generated file and inject the incidents one by one according to their time stamps.
1. Put all needed incident sample files under incidents_samples dir.
	- The files should be in JSON format, as shown in the preloaded samples under the ./incidents_samples dir.
2. Navigate to ./config dir and edit the configFile.txt as instructed (explanation of how / where to edit is located both in the configFile and its local README file).
3. Navigate to ./Source_Files, and run the IncidentJsonGenerator.py python script using:
	- python3 IncidentJsonGenerator.py
4. for other usage options use the -h flag.
	NOTE: it is also possible to run all template incidents in a circular way, at a specific rate using the -r/-d flags alone.

At this point, the generated JSON file will be located here: ./generated_output/mock_generated_incidents.json

5. Using the generated file is done by editing the "ids-ppe/config/brain_simulation_config.json" where for "ids-ppe" is the root for the entire git repository.
	- change the value for: "brain_notifications_player_enabled" to true
	- change the value for: "brain_notifications_player_file" to <mock_generated_incidents_path>
	NOTE: it is recomended to just move the mock_generated_incidents.json to the running dir, which should be "ids-ppe/output", and then <mock_generated_incidents_path> should be just "./mock_generated_incidents.json"
6. now just run the brain.exe and the incidents should be injected as their time stamps shows.


Script usage:
---------------------------------------------

usage: IncidentJsonGenerator.py <options>
<options> = [-h|--help] [-r|--rate <rate>] [-d|--duration <duration>] [-c|--config <fileName>]

no flags        will search for a default config file and read its content in the following
                format: "sample_name.json <rate> <duration>"
                <rate> is an integer marking the amount of incidents per seconds.
                <duration> is an integer marking the amount of seconds incidents of that
                type will continue to be injected.
-r, --rate      determine the rate of which the incidents appear as a poisson distribution
                parameter - average rate of appearance per second.
-d, --duration  determine the amount of time in seconds that incidents are to be reported.
-c, --config    change the config file to be read - only its name, when it is located inside
                the config dir.
-h, --help      print this message