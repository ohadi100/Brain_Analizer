#!/usr/bin/env/python
import sys, os, json, getopt

"""
=================================
set global vars 				:
=================================
"""
g_rootDir = os.path.abspath(os.path.dirname(sys.argv[0])) + '\..'
g_templatesDir = g_rootDir +'\\incidents_samples'
g_configFileDir = g_rootDir + '\\config'
g_outputDir = g_rootDir + '\\generated_output'
g_outputFile = g_outputDir + '\\mock_generated_incidents.json'

"""
=================================
define IncidentGenerator class 	:
=================================
"""
# the IncidentGenerator class reads the input CLI and generates the JSON incidents accordingly:
class IncidentGenerator:
	MAX_INCIDENTS_AMOUNT = 1000000
	# the number of incidents per second:
	m_inputRate = 1
	# the number of seconds the incidents are reported:
	m_inputDuration = 1
	# configuration file mode flag:
	m_isConfigFileMode = False
	# the saved templates in a dictionary:
	m_templates = {}
	# an array that matches an index to a specific template:
	m_indexToTemplate = []
	# the current incident's time offset:
	m_currentIncidentOffset = 0
	# the config file to be read:
	m_configFile = ""

	def printHelpMessage():
		print(																									)
		print('usage: IncidentJsonGenerator.py <options>'														)
		print('<options> = [-h|--help] [-r|--rate <rate>] [-d|--duration <duration>] [-c|--config <fileName>]'	)
		print(																									)
		print('no flags        will search for a default config file and read its content in the following' 	)
		print('                format: \"sample_name.json <rate> <duration>\"'									)
		print('                <rate> is an integer marking the amount of incidents per seconds.'				)
		print('                <duration> is an integer marking the amount of seconds incidents of that'		)
		print('                type will continue to be injected.'												)
		print('-r, --rate      determine the rate of which the incidents appear as a poisson distribution' 		)
		print('                parameter - average rate of appearance per second.'								)
		print('-d, --duration  determine the amount of time in seconds that incidents are to be reported.'		)
		print('-c, --config    change the config file to be read - only its name, when it is located inside'	)
		print('                the config dir.'																	)
		print('-h, --help      print this message'																)

	"""
	The getInputArguments function will read the CLI arguments and set the member variables 
	accordingly.
	""" 
	def getInputArguments(self, argv):	
		print('=============================================================')
		print('||               Starting script message                   ||')
		print('=============================================================')
		try:
			# get the options from CLI arguments:
			opts, args = getopt.getopt(argv,"hr:d:c:",["rate=","duration=","config="])
		except getopt.GetoptError:
			# print proper usage in case an error occured:
			IncidentGenerator.printHelpMessage()
			sys.exit(2)
		if 0 == len(opts):
			self.m_isConfigFileMode = True
			self.m_configFile = g_configFileDir + '\\configFile.txt'
			print('No arguments were found.')
			print('The default operation is reading the config file and generate incidents accordingly.')
			print('Chosen default config file is: \"',self.m_configFile,'\"',sep='')
			return
		# for every option:
		for opt, arg in opts:
			# if help is needed, show full usage and exit:
			if opt in ('-h', "--help"):
				IncidentGenerator.printHelpMessage()
				sys.exit()
			# if rate option is set, save the rate of incident appearance.
			elif opt in ("-r", "--rate"):
				self.m_inputRate = int(arg)
				if self.m_inputRate <= 0:
					print("Illegal non-positive rate input. Rate was set with a default value = 1.")
					self.m_inputRate = 1
			# if duration option is set, save the duration that incidents will keep appearing.
			elif opt in ("-d", "--duration"):
				self.m_inputDuration = int(arg)
				if self.m_inputDuration <= 0:
					print("Illegal non-positive duration input. Duration was set with a default value = 1.")
					self.m_inputDuration = 1
			elif opt in ("-c", "--config"):
				self.m_isConfigFileMode = True
				self.m_configFile = g_configFileDir + '\\' + arg
				print('config file changed from default to: \"',self.m_configFile,'\"',sep='')
			else:
				print('wrong usage, try using \"-h\" flag for further assistance')
				exit 
		print('Input duration is set to: ', self.m_inputDuration, ' seconds')
		print('Input rate is set to    : ', self.m_inputRate, ' incidents per second')
		if self.MAX_INCIDENTS_AMOUNT < (self.m_inputDuration * self.m_inputRate):
			print("NOTIFICATION: too many incidents are set using this rate * duration combination, amount is set to ",
				self.MAX_INCIDENTS_AMOUNT, " and will stop after approximately ", self.MAX_INCIDENTS_AMOUNT/self.m_inputRate, " seconds")

	"""
	The setNextTimeOffset calculates the next timestamp offset for the incident, and saves the current in the member timestamp variable
	"""
	def setNextTimeOffset(self, rate):
		# retruned ammount is in miliseconds:
		self.m_currentIncidentOffset += 1000 / rate
	
	"""
	The maxAmountExceeded function checks if the max amount of incidents exceeded
	"""
	def maxAmountExceeded(self, amount):
		if self.MAX_INCIDENTS_AMOUNT < amount:
			print('max incident amount exceeded:',self.MAX_INCIDENTS_AMOUNT)
			return True
		return False

	"""
	The templateToIncidentData function generates a string out of a json template and the next timestamp
	"""
	def templateToIncidentData(self, name, rate):
		# calculate the next event's time stamp (miliseconds offset from clock start):
		self.setNextTimeOffset(rate)
		# load as a JSON structure:
		data = self.m_templates[name]
		# set the timestamp to the proper value:
		data['timestamp'] = self.m_currentIncidentOffset
		# change the data's format
		return json.dumps(data,indent='\t', separators=(',', ': '))

	"""
	The lineToIncidents function reads a config file line, and generates the desired json using the templates name, rate and duration noted in the line.
	"""
	def lineToIncidents(self, currentIncidentsAmount, configLine):
		# split line into the three fields it contain:
		name, rate, duration = configLine.split()
		# calculate how many incidents are to be reported:
		addedIncidentAmount = int(rate) * int(duration)
		# check that the max amount of incidents is no exceeded:
		if self.maxAmountExceeded(currentIncidentsAmount + addedIncidentAmount):
			return '', 0
		firstIteration = True
		data = ''
		for i in range(addedIncidentAmount):
			# if this is not the first element in a list, we need to add a comma beforehand:
			if not firstIteration:
				data += ","
			else:
				firstIteration = False
			# generate a json data out of the template:
			data += self.templateToIncidentData(name, int(rate))
		return data, addedIncidentAmount

	"""
	The genIncidentsFromFile will generate the file using a pre-made config file.
	"""
	def genIncidentsFromFile(self):
		print('Generating new JSON from config file.')
		currentIncidentsAmount = 0
		# read config file and generate the output file using the templates:
		with open(self.m_configFile, 'r') as config_file, open(g_outputFile, 'w') as json_output_file:
				# in order to make a list of JSONs create a list:
				json_output_file.write('[')
				firstIteration = True
				for line in config_file:
					if '#' not in line and line not in ['\n', '\r\n']:
						tmpAmount = 0
						data = ''
						if not firstIteration:
							json_output_file.write(",")
						else:
							firstIteration = False
						data, tmpAmount = self.lineToIncidents(currentIncidentsAmount, line)
						if 0 < tmpAmount:
							currentIncidentsAmount += tmpAmount
							json_output_file.write(data)
						else:
							break
				# end the list:
				json_output_file.write(']')
				# close file:
				json_output_file.close()
			

	"""
	The genIncidentsFromArguments will generate the file using the CLI arguments configuration.
	"""
	def genIncidentsFromArguments(self):
		print('Generating new JSON from argument.')
		# set params:
		incidentTime = 0
		incidentsAmount = int(self.m_inputDuration * self.m_inputRate)
		if self.MAX_INCIDENTS_AMOUNT < incidentsAmount:
			incidentsAmount = self.MAX_INCIDENTS_AMOUNT
		# generate the output file using the templates
		with open(g_outputFile, 'w') as json_output_file:
			# in order to make a list of JSONs create a list:
			json_output_file.write('[')
			firstIteration = True
			for i in range(incidentsAmount):
				if not firstIteration:
					json_output_file.write(",")
				else:
					firstIteration = False
				# generate the next event's data:
				data = self.templateToIncidentData(self.m_indexToTemplate[i % len(self.m_templates)], self.m_inputRate)
				# write generated json into the output file, using the comma sign as a separator:
				json_output_file.write(data)
			# end the list:
			json_output_file.write(']')
			# close file:
			json_output_file.close()
	
	"""
	The generateIncidentsFile function will read the JSON templates, and generate a 
	massive JSON file containing incidents from each of the templates. The templates
	will be duplicated with different time stamps according to the different parameters.
	"""
	def generateIncidentsFile(self):
		print() 
		# read templates and save internally:
		for filename in os.listdir(g_templatesDir):
			if os.path.isfile(g_templatesDir + '\\' + filename):
				print('Reading template: "', filename, '"',sep="")
				fullFilePath = g_templatesDir + '\\' + filename
				# add template to template DB:
				with open(fullFilePath) as json_template:
					#  save the data to the internally stored templates array:
					self.m_templates[filename] = json.load(json_template)
					self.m_indexToTemplate += [filename]
					json_template.close()
		print('=====', len(self.m_indexToTemplate), 'templates were read', '=====')
		print()
		if self.m_isConfigFileMode:
			self.genIncidentsFromFile()
		else:
			self.genIncidentsFromArguments()

"""
=================================
main function definition	 	:
=================================
"""
def main(argv):
	# create the IncidentGenerator instance:
	ig = IncidentGenerator()

	# read the CLI arguments:
	ig.getInputArguments(argv)
	# read the samples and generate the output JSON file:
	ig.generateIncidentsFile()

"""
=================================
running section				 	:
=================================
"""
if __name__ == "__main__":
	main(sys.argv[1:])