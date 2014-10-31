# Makefile para el caso 4 de la LIBRERÍA
# ©2010-11 Inma, Gerardo, Fidel, Juanma, Antonio
#
# --- Parte configurable ---
#
# NOMBREALUMNO es el nombre del directorio donde el alumno guarda las
# prácticas de POO (C++). Dentro de ese directorio debe haber uno para
# cada práctica llamado NOMBREPRACTICA, que será de la forma P<n>,
# siendo <n> el número de práctica: P0, P1, etc.

NOMBREALUMNO   = MA1113_ValleCabreraRafael
NOMBREPRACTICA = P4

# CADENADIR y FECHADIR son los directorios donde están respectivamente
# los módulos objeto y cabeceras de Cadena y Fecha: cadena.{oh} y fecha.{oh}.
DIRFECHACADENA=P1
CADENADIR= ../${DIRFECHACADENA}/Cadena
FECHADIR = ../${DIRFECHACADENA}/Fecha

# ¿Compilador C++ de Intel (icpc) o de GNU (g++)?
#CXX      = icpc
CXX	 = g++

ifeq (${CXX},icpc)
  CXXFLAGS = -g -Wall ${INCLUDES}
else
  CXXFLAGS = -g -ansi -pedantic -Wall ${INCLUDES}
endif
# --- Fin parte configurable

INCLUDES  = -I${CADENADIR} -I${FECHADIR}
LOCALLIBS = ${CADENADIR}/cadena.o ${FECHADIR}/fecha.o
EXTLIBS   = -lcrypt
LIBS      = ${LOCALLIBS} ${EXTLIBS}
VPATH     = .:${CADENADIR}:${FECHADIR}

COMM_SRCS = usuario.cpp tarjeta.cpp articulo.cpp pedido.cpp pedido-articulo.cpp
MAIN_SRCS = $(COMM_SRCS) test-caso4-consola.cpp
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)
MAIN_EXE  = test-caso4-consola
TEST_SRCS = $(COMM_SRCS) test-caso0-cadena-auto.cpp test-caso0-fecha-auto.cpp \
  test-caso1-auto.cpp test-caso3-auto.cpp test-caso4-auto.cpp test-auto.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_EXE  = test-p1_4-auto

NOMBRETAR = ../../${NOMBREALUMNO}.tar.gz
NOMBREDIR = ${NOMBREALUMNO}/${NOMBREPRACTICA}

## OBJETIVOS PRINCIPALES #######################################################

.PHONY: all clean dist distclean test-consola test-auto

all: ${MAIN_EXE} ${TEST_EXE}

test-consola: ${MAIN_EXE}
	./$<

test-auto: ${TEST_EXE}
	./$<

clean:
	${RM} ${RMFLAGS} ${MAIN_EXE} ${MAIN_OBJS} ${TEST_EXE} ${TEST_OBJS} \
		*.{aux,log,dvi,toc} *~ \#* *.d
	(cd ${FECHADIR}; make clean)
	(cd ${CADENADIR}; make clean)

## COMPILACIÓN #################################################################

${MAIN_EXE}: ${MAIN_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

${TEST_EXE}: ${TEST_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

# Detección automática de dependencias en código fuente C++ con GCC #

%.d: %.cpp
	@$(CXX) -MM $(CXXFLAGS) $< > $@
	@sed -ri 's,($*)\.o[ :]*,\1.o $@ : ,g' $@

-include $(MAIN_SRCS:.cpp=.d) $(TEST_SRCS:.cpp=.d)

## EMPAQUETADO #################################################################

${NOMBRETAR}: ${SRCS} ${HDRS}
ifeq ($(strip $(NOMBREALUMNO)),)
	@echo ""
	@echo "ATENCIÓN: debe definir en el Makefile la variable NOMBREALUMNO"
	@echo "con el nombre del directorio superior a este."
	@echo " Vea las instrucciones de entrega de las prácticas."
else
	tar -cvz -C../.. -f ${NOMBRETAR} ${NOMBREDIR} \
				${NOMBREALUMNO}/${DIRFECHACADENA}
endif

# Esto lo deberían usar los alumnos a la hora de la entrega:
# crea el archivo .tar.gz en el directorio padre tras borrar lo sobrante.
dist: clean ${NOMBRETAR}

distclean: clean
	${RM} ${RMFLAGS} ${NOMBRETAR}
