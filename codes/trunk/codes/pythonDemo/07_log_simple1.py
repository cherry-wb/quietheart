#!/usr/bin/python
import logging

if "__main__" == __name__:
    ######simple Here, logging act as a global, amount many modules.
    #logging.debug("default level.")
    #logging.info("default level.")
    #logging.error("default level.")

    #logging.basicConfig(level=logging.DEBUG) #one-off configuration, subsequent call no use.
    logging.basicConfig(format='%(name)s:%(asctime)s--%(filename)s:%(funcName)s:%(lineno)d:%(levelname)s>>>:%(message)s', level=logging.DEBUG)
    #logging.basicConfig(filename='./example.log',filemode='w',level=logging.DEBUG)
    logging.debug("debug level.")
    logging.info("debug level.")
    logging.error("debug level.")

    #logging.basicConfig(level=logging.INFO)
    logging.debug("info level.")
    logging.info("info level.")
    logging.error("info level.")

    #logging.basicConfig(level=logging.ERROR)
    logging.debug("error level.")
    logging.info("error level.")
    logging.error("error level.")
    logging.log(logging.ERROR,"error by log.")
