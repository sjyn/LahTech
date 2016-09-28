#-=-=-=-=-=-=-=-=-=-=-=-=-=-
#ohm.py
#Steven Rosendahl
#-=-=-=-=-=-=-=-=-=-=-=-=-=-
import re

def solve(list):
	count = 1
	ret = []
	for problem in list :
		nums = re.findall(r"\d+.\d+|\.\d+|\d+",problem)
		goingA = re.findall(r"P=|E=",problem)
		if len(goingA) == 2:
			unitsP = re.findall(r"P=\wW|\wW",problem)
			unitsE = re.findall(r"E=\wV|\wV",problem)
			#P -> E
			if goingA[0] == "P=" and goingA[1] == "E=":
				power = float(nums[0])
				volts = float(nums[1])
			#E -> P
			else:
				volts = float(nums[0])
				power = float(nums[1])
			power = float(adjustForUnit(unitsP[0],power,"W"))
			volts = float(adjustForUnit(unitsE[0],volts,"V"))
			current = power / volts
			ret.append("Problem #" + str(count) + ":I=" + "{0:.2f}".format(current) + "A")
		goingB = re.findall(r"P=|I=",problem)
		if len(goingB) == 2:
			unitsP = re.findall(r"P=\wW|\wW",problem)
			unitsI = re.findall(r"I=\wA|\wA",problem)
			#P -> I
			if goingB[0] == "P=" and goingB[1] == "I=":
				power = float(nums[0])
				amps = float(nums[1])
			#I -> P
			else:
				amps = float(nums[0])
				power = float(nums[1])
			# print power
			amps = float(adjustForUnit(unitsI[0],amps,"A"))
			power = float(adjustForUnit(unitsP[0],power,"W"))
			# print unitsP[0]
			volts = power / amps
			ret.append("Problem #" + str(count) + ":E=" + "{0:.2f}".format(volts) + "V")
		goingC = re.findall(r"E=|I=",problem)
		if len(goingC) == 2:
			unitsE = re.findall(r"E=\wV|\wV",problem)
			unitsI = re.findall(r"I=\wA|\wA",problem)
			#E -> I
			if goingC[0] == "E=" and goingC[1] == "I=":
				volts = float(nums[0])
				amps = float(nums[1])
			#I -> E
			else:
				amps = float(nums[0])
				volts = float(nums[1])
			volts = float(adjustForUnit(unitsE[0],volts,"V"))
			amps = float(adjustForUnit(unitsI[0],amps,"A"))
			power = volts * amps
			ret.append("Problem #" + str(count) + ":P=" + "{0:.2f}".format(power) + "W")
		count = count + 1
	return ret

def adjustForUnit(adjustee, number, baseUnit):
	if re.search("m" + baseUnit, adjustee):
		return repr(float(number) / 1000.0)
	elif re.search("k" + baseUnit,adjustee):
		return repr(float(number) * 1000.0)
	elif re.search("M" + baseUnit,adjustee):
		return repr(float(number) * 1000000.0)
	else:
		return repr(number)