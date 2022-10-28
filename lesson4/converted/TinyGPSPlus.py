from curses.ascii import isdigit
from dataclasses import dataclass
from math import comb, degrees, radians, sin, cos, sqrt, atan2

# System Config
_GPS_VERSION = "1.0.2"
_GPS_MPH_PER_KNOT = 1.15077945
_GPS_MPS_PER_KNOT = 0.51444444
_GPS_KMPH_PER_KNOT = 1.852
_GPS_MILES_PER_METER = 3.2808399
_GPS_KM_PER_METER = 0.001
_GPS_FEET_PER_METER = 3.2808399
_GPS_MAX_FIELD_SIZE = 15

# Constants
_GPRMCterm = "GPRMC"
_GPGGAterm = "GPGGA"
_GNRMCterm = "GNRMC"
_GNGGAterm = "GNGGA"

ULONG_MAX = 4294967295 # Maximum 32-bit integer size

TWO_PI = 0 # TODO: Make correct

# Enums
GPS_SENTENCE_GPGGA = 0
GPS_SENTENCE_GPRMC = 1
GPS_SENTENCE_OTHER = 2

# Helpers
# TODO: find Pico version of millis() (returns number of milliseconds since program execution began)
def millis():
    return 1

def COMBINE(sentenceType, termNumber):
    return sentenceType << 5 | termNumber

# Structs
@dataclass
class RawDegrees:
    deg: int
    billionths: int
    negative: bool

    def __init__(self):
        self.deg = 0
        self.billionths = 0
        self.negative = False
    
@dataclass
class TinyGPSLocation:
    # private
    __valid: bool
    __updated: bool
    __rawLatData: RawDegrees
    __rawLngData: RawDegrees
    __rawNewLatData: RawDegrees
    __rawNewLngData: RawDegrees
    __lastCommitTime: int

    def __init__(self):
        self.valid = False
        self.updated = False

    def isValid(self):
        return self.__isValid
    
    def isUpdated(self):
        return self.__isUpdated

    def age(self):
        return millis() - self.__lastCommitTime if self.valid else ULONG_MAX
    
    def lat(self):
        self.__updated = False
        ret = self.__rawLatData.deg + self.__rawLatData.billionths / 1000000000.0
        return -ret if self.__rawLatData.negative else ret

    def long(self):
        self.__updated = False
        ret = self.__rawLngData.deg + self.__rawLngData.billionths / 1000000000.0
        return -ret if self.__rawLngData.negative else ret
    
    def rawLat(self):
        self.__updated = False
        return self.__rawLatData
    
    def rawLng(self):
        self.__updated = False
        return self.__rawLngData

    def __commit(self):
        self.__rawLatData = self.__rawNewLatData
        self.__rawLngData = self.__rawNewLngData
        self.__lastCommitTime = millis()
        self.__valid = True
        self.__updated = True
    
    def __setLatitude(self, term):
        TinyGPSPlus.parseDegrees(term, self.__rawNewLatData)

    def __setLongitude(self, term):
        TinyGPSPlus.parseDegrees(term, self.__rawNewLongData)


@dataclass
class TinyGPSDate:
    # private
    __valid: bool
    __updated: bool
    __date: int
    __newDate: int
    __lastCommitTime: int

    def __init__(self):
        self.__valid = False
        self.__updated = False
        self.__date = 0

    def isValid(self):
        return self.__isValid
    
    def isUpdated(self):
        return self.__isUpdated

    def age(self):
        return millis() - self.__lastCommitTime if self.valid else ULONG_MAX
    
    def value(self):
        self.__updated = False
        return self.__date

    def year(self):
        self.__updated = False
        year = self.__date % 100
        return year + 2000

    def month(self):
        self.__updated = False
        return (self.__date / 100) % 100
    
    def day(self):
        self.__updated = False
        return self.__date / 10000

    def __commit(self):
        self.__date = self.__newDate
        self.__lastCommitTime = millis()
        self.__valid = True
        self.__updated = True
    
    def __setDate(self, term):
        self.__newDate = int(term)

@dataclass
class TinyGPSTime:
    # private
    __valid: bool
    __updated: bool
    __time: int
    __newTime: int
    __lastCommitTime: int

    def __init__(self):
        self.__valid = False
        self.__updated = False
        self.__time = 0

    def isValid(self):
        return self.__isValid
    
    def isUpdated(self):
        return self.__isUpdated

    def age(self):
        return millis() - self.__lastCommitTime if self.valid else ULONG_MAX
    
    def value(self):
        self.__updated = False
        return self.__date

    def hour(self):
        self.__update = False
        return self.__time / 1000000

    def minute(self):
        self.__update = False
        return (self.__time / 10000) % 100

    def second(self):
        self.__update = False
        return (self.__time / 100) % 100
    
    def centisecond(self):
        self.__update = False
        return self.__time % 100

    def __commit(self):
        self.__time = self.__newTime
        self.__lastCommitTime = millis()
        self.__valid = True
        self.__updated = True
    
    def __setTime(self, term):
        self.__newTime = TinyGPSPlus.parseDecimal(term)

@dataclass
class TinyGPSDecimal:
    # TODO: shouldn't values be floats?
    # private
    __valid: bool
    __updated: bool
    __val: int
    __newVal: int

    def __init__(self):
        self.__valid = False
        self.__updated = False
        self.val = 0

    def isValid(self):
        return self.__isValid
    
    def isUpdated(self):
        return self.__isUpdated

    def age(self):
        return millis() - self.__lastCommitTime if self.valid else ULONG_MAX
    
    def value(self):
        self.__updated = False
        return self.__val

    def __commit(self):
        self.__val = self.__newVal
        self.__lastCommitTime = millis()
        self.__valid = True
        self.__updated = True
    
    def __set(self, term):
        self.__newVal = TinyGPSPlus.parseDecimal(term)

@dataclass
class TinyGPSInteger:
    # private
    __valid: bool
    __updated: bool
    __val: int
    __newVal: int

    def __init__(self):
        self.__valid = False
        self.__updated = False
        self.val = 0

    def isValid(self):
        return self.__isValid
    
    def isUpdated(self):
        return self.__isUpdated

    def age(self):
        return millis() - self.__lastCommitTime if self.valid else ULONG_MAX
    
    def value(self):
        self.__updated = False
        return self.__val

    def __commit(self):
        self.__val = self.__newVal
        self.__lastCommitTime = millis()
        self.__valid = True
        self.__updated = True
    
    def __set(self, term):
        self.__newVal = int(float(term))

@dataclass
class TinyGPSSpeed(TinyGPSDecimal):
    def knots(self):
        return self.value() / 100.0
    
    def mph(self):
        return self.value() * _GPS_MPH_PER_KNOT / 100.0
    
    def mps(self):
        return self.value() * _GPS_MPS_PER_KNOT / 100.0

    def kmph(self):
        return self.value() * _GPS_KMPH_PER_KNOT / 100.0

@dataclass
class TinyGPSCourse(TinyGPSDecimal):
    def deg(self):
        return self.value() / 100.0

@dataclass
class TinyGPSAltitude(TinyGPSDecimal):
    def meters(self):
        return self.value() / 100.0

    def miles(self):
        return self.value() * _GPS_MILES_PER_METER / 100.0
    
    def kilometers(self):
        return self.value() * _GPS_KM_PER_METER / 100.0

    def feet(self):
        return self.value() * _GPS_FEET_PER_METER / 100.0
    
@dataclass
class TinyGPSHDOP(TinyGPSDecimal):
    def hdop(self):
        return self.value() / 100.0

class TinyGPSPlus:
    pass

class TinyGPSCustom(TinyGPSPlus):
    pass

class TinyGPSCustom(TinyGPSPlus):
    # private
    __valid: bool
    __updated: bool
    __stagingBuffer: list
    __buffer: list
    __lastCommitTime: int
    __sentenceName: str
    __termNumber: int
    __next: TinyGPSCustom # Python doesn't like the self reference, TODO: allow self reference

    def __init__(self):
        pass

    def __init__(self, gps, sentenceName, termNumber):
        self.begin(gps, sentenceName, termNumber)

    def begin(self, gps, sentenceName, termNumber):
        self.__lastCommitTime = 0
        self.__valid = True
        self.__updated = True
        self.__sentenceName = sentenceName
        self.__termNumber = termNumber
        self.__stagingBuffer = "\0" * len(self.__stagingBuffer)
        self.__buffer = "\0" * len(self.__buffer)

        self.__gps.insertCustom(gps, sentenceName, termNumber)

    def isValid(self):
        return self.__isValid
    
    def isUpdated(self):
        return self.__isUpdated

    def age(self):
        return millis() - self.__lastCommitTime if self.valid else ULONG_MAX
    
    def value(self):
        self.__updated = False
        return self.__buffer

    def __commit(self):
        self.__buffer = self.__stagingBuffer
        self.__lastCommitTime = millis()
        self.__valid = True
        self.__updated = True

    def __set(self, term):
        self.__stagingBuffer = term * len(self.__stagingBuffer)
    
class TinyGPSPlus:
    # public

    location: TinyGPSLocation
    date: TinyGPSDate
    time: TinyGPSTime
    speed: TinyGPSSpeed
    course: TinyGPSCourse
    altitude: TinyGPSAltitude
    satellites: TinyGPSInteger
    hdop: TinyGPSHDOP

    # private
    # TODO: figure out enum translation
    # enum {GPS_SENTENCE_GPGGA, GPS_SENTENCE_GPRMC, GPS_SENTENCE_OTHER};

    __parity: int
    __isChecksumTerm: bool
    __term: str
    __curSentenceType: int
    __curTermNumber: int
    __curTermOffset: int
    __sentenceHasFix: bool

    __customElts: TinyGPSCustom
    __customCandidates: TinyGPSCustom

    __encodedCharCount: int
    __sentencesWithFixCount: int
    __failedChecksumCount: int
    __passedChecksumCount: int

    def __init__(self):
        self.__parity = 0
        self.__isChecksumTerm = False
        self.__curSentenceType(GPS_SENTENCE_OTHER)
        self.__customElts = None

    def encode(self, c):
        self.__encodedCharCount += 1

        if c == ",":
            pass
        elif c == "\r" or c == "\n" or c == "*":
            isSentenceValid = False
            if self.__curTermOffset < len(self.__term):
                self.__term[self.__curTermOffset] = 0
                isValidSentence = self.__endOfTermHandler()
            
            self.__curTermNumber += 1
            self.__curTermOffset = 0
            self.__isChecksumTerm = c == "*"
            return isValidSentence
        elif c == "$":
            self.__curTermNumber = 0
            self.__curTermOffset = 0
            self.__parity = 0
            self.__curSentenceType = GPS_SENTENCE_OTHER
            self.__isChecksumTerm = False
            self.__sentenceHasFix = False
            return False
        else:
            if self.__curTermOffset < len(self.__term) - 1:
                self.term[self.__curTermOffset] = c
                self.__curTermOffset += 1
            if not self.__isChecksumTerm:
                self.__parity ^= c # TODO: variables here need to be changed to deal with bitwise operations
            return False


    # TODO: Figure out what this means
    # TinyGPSPlus &operator << (char c) {encode(c); return *this;}

    def libraryVersion():
        return _GPS_VERSION

    def distanceBetween(self, lat1, long1, lat2, long2):
        delta = radians(long1 - long2)
        sdlong = sin(delta)
        cdlong = cos(delta)
        lat1 = radians(lat1)
        lat2 = radians(lat2)
        slat1 = sin(lat1)
        clat1 = cos(lat1)
        slat2 = sin(lat2)
        clat2 = cos(lat2)

        delta = (clat1 * slat2) - (slat1 * clat2 * cdlong)
        delta = sqrt(delta)
        delta += sqrt(clat2 * sdlong)
        delta = sqrt(delta)

        denom = (slat1 * slat2) + (clat1 * clat2 * cdlong)
        delta = atan2(delta, denom)
        return delta * 6372795


    def courseTo(self, lat1, long1, lat2, long2):
        dlon = radians(long2 - long1)
        lat1 = radians(lat1)
        lat2 = radians(lat2)
        a1 = sin(dlon) * cos(lat2)
        a2 = sin(lat1) * cos(lat2) * cos(dlon)

        a2 = cos(lat1) * sin(lat2) - a2
        a2 = atan2(a1, a2)
        if a2 < 0.0:
            a2 += TWO_PI # TODO: add two pi
            
        return degrees(a2)

    def cardinal(self, course):
        directions = ["N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE", "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW"]
        direction = int((course + 11.25) / 22.5)

        return directions[direction % 16]

    def parseDecimal(self, term):
        negative = term == '-'
        if negative:
            term += 1
        ret = 100 * term
        pass

    def parseDegrees(term, deg: RawDegrees):
        leftOfDecimal = int(float(term))
        minutes = leftOfDecimal % 100
        multiplier = 10000000
        tenMillionthsOfMinutes = minutes * multiplier

        deg.deg = leftOfDecimal / 100

        # TODO: Figure out what term is and how to use it
        index = 0
        while isdigit(term[index]):
            index += 1
        
        if term[index] == ".":
            while isdigit(term[index + 1]):
                index += 1
                multiplier /= 10
                tenMillionthsOfMinutes += (ord(term[index]) - ord("0")) * multiplier
        
        # Double check order of operations
        deg.billionths = (5 * tenMillionthsOfMinutes + 1) / 3
        deg.negative = False


    def charsProcessed(self):
        return self.__encodedCharCount

    def sentencesWithFix(self):
        return self.__sentencesWithFixCount

    def failedChecksum(self):
        return self.__failedChecksumCount

    def passedChecksum(self):
        return self.__passedChecksumCount

    def __insertCustom(pElt: TinyGPSCustom, sentenceName: str, termNumber: int):
        current = pElt.__customElts
        while current != None:
            if sentenceName < current.__sentenceName or (sentenceName == current.__sentenceName and termNumber < current.__termNumber):
                break
        
        pElt.next = current

    def __fromHex(self, a):
        if a >= 'A' and a <= 'F':
            return a - 'A' + 10
        elif a >= 'a' and a <= 'f':
            return a - 'a' + 10
        else:
            return a - '0'

    def __endOfTermHandler(self):
        if self.__isChecksumTerm:
            # TODO: figure this out
            checksum = 16 * self.__fromHex(self.__term[0]) + self.__fromHex(self.__term[1])
            checksum = 0
            if checksum == self.__parity:
                self.__passedChecksumCount += 1
                if self.__sentenceHasFix:
                    self.__sentencesWithFixCount += 1
                
                if self.__curSentenceType == GPS_SENTENCE_GPRMC:
                    self.date.__commit()
                    self.time.__commit()

                    if self.__sentenceHasFix:
                        self.location.__commit()
                        self.speed.__commit()
                        self.course.__commit()
                elif self.__curSentenceType == GPS_SENTENCE_GPGGA:
                    self.time.__commit()
                    if self.__sentenceHasFix:
                        self.location.__commit()
                        self.speed.__commit()
                        self.course.__commit()
                    self.satellites.__commit()
                    self.hdop.__commit()
                
                current = self.__customCandidates
                while current != None and current.__sentenceName == self.__customCandidates.__sentenceName:
                    current.__commit()
                    current = current.__next
                
                return True
            else:
                self.__failedChecksumCount += 1
            
            return False
        
        if self.__curTermNumber == 0:
            if self.__term == _GPRMCterm or self.__term == _GNRMCterm:
                self.__curSentenceType = GPS_SENTENCE_GPRMC
            elif self.__term == _GPGGAterm or self.__term == _GNGGAterm:
                self.__curSentenceType = GPS_SENTENCE_GPGGA
            else:
                self.__curSentenceType = GPS_SENTENCE_OTHER

            self.__customCandidates = self.__customElts
            while self.__customCandidates != None and self.__customCandidates.__sentenceName < self.__term:
                self.__customCandidates = self.__customCandidates.__next
            
            if self.__customCandidates != None and self.__customCandidates.__sentenceName > self.__term:
                self.__customCandidates = None

            return False
        
        if self.__curSentenceType != GPS_SENTENCE_OTHER and term[0]:
            combination = COMBINE(self.__curSentenceType, self.__curTermNumber)
            if combination == COMBINE(GPS_SENTENCE_GPRMC, 1) or combination == COMBINE(GPS_SENTENCE_GPGGA, 1): # Time in both sentences
                self.time.__setTime(self.__term)
            elif combination == COMBINE(GPS_SENTENCE_GPRMC, 2): # GPMRC validity
                self.__sentenceHasFix = self.__term[0] == "A" 
            elif combination == COMBINE(GPS_SENTENCE_GPRMC, 3) or combination == COMBINE(GPS_SENTENCE_GPGGA, 2): # Latitude
                self.location.__setLatitude(self.__term)
            elif combination == COMBINE(GPS_SENTENCE_GPRMC, 4) or combination == COMBINE(GPS_SENTENCE_GPGGA, 3): # N/S
                self.location.__rawNewLatData.negative = self.__term[0] == "S"
            elif combination == COMBINE(GPS_SENTENCE_GPRMC, 5) or combination == COMBINE(GPS_SENTENCE_GPGGA, 4): # Longitude
                self.location.__setLongitude(self.__term)
            elif combination == COMBINE(GPS_SENTENCE_GPRMC, 6) or combination == COMBINE(GPS_SENTENCE_GPGGA, 5): # E/W
                self.location.__rawNewLngData.negative = self.__term[0] == "W"
            elif combination == COMBINE(GPS_SENTENCE_GPRMC, 7): # Speed (GPRMC)
                self.speed.__set(self.__term)
            elif combination == COMBINE(GPS_SENTENCE_GPRMC, 8): # Course (GPMRC)
                self.course.__set(self.__term)
            elif combination == COMBINE(GPS_SENTENCE_GPRMC, 9): # Date (GPMRC)
                self.date.__set(self.__term)
            elif combination == COMBINE(GPS_SENTENCE_GPGGA, 6): # Fix data (GPGGA)
                self.__sentenceHasFix = ord(self.__term[0]) > ord("0")
            elif combination == COMBINE(GPS_SENTENCE_GPGGA, 7): # Satellites used (GPGGA)
                self.satellites.__set(self.__term)
            elif combination == COMBINE(GPS_SENTENCE_GPGGA, 8): # HDOP
                self.hdop.__set(self.__term)
            elif combination == COMBINE(GPS_SENTENCE_GPGGA, 9):
                self.altitude.__set(self.__term)
        
        current = self.__customCandidates
        while current != None and current.__sentenceName == self.__customCandidates.__sentenceName:
            if current.__termNumber == self.__curTermNumber:
                current.__set(self.__term)
            current = current.__next
        
        return False
            