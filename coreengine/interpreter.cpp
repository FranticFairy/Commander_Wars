#include "coreengine/interpreter.h"
#include "coreengine/console.h"
#include "coreengine/mainapp.h"

#include <QDir>
#include <QQmlEngine>
#include <QTextStream>

Interpreter::Interpreter(const QString& script, QObject *parent)
    : QQmlEngine(parent)
{
    init();
    openScript(script);
}

Interpreter::Interpreter(QObject *parent)
    : QQmlEngine(parent)
{
    init();
}

void Interpreter::init()
{
    Mainapp* pApp = Mainapp::getInstance();
    QJSValue globals = newQObject(pApp);
    globalObject().setProperty("globals", globals);
    QJSValue audio = newQObject(pApp->getAudioThread());
    globalObject().setProperty("audio", audio);

    QJSValue console = newQObject(Console::getInstance());
    globalObject().setProperty("GameConsole", console);
    installTranslatorFunctions();
}

void Interpreter::openScript(const QString& script)
{
    QFile scriptFile(script);
    if (!scriptFile.open(QIODevice::ReadOnly))
    {
        QString error = "Error: attemp to read File " + script + " which couldn't be opened.";
        Console::print(error, Console::eERROR);
    }
    else
    {
        QTextStream stream(&scriptFile);
        QString contents = stream.readAll();
        scriptFile.close();
        QJSValue value = evaluate(contents, script);
        if (value.isError())
        {
            QString error = value.toString() + " in File:" + script;
            Console::print(error, Console::eERROR);
        }
    }
}

Interpreter::~Interpreter()
{
    // free memory
   collectGarbage();
}


QJSValue Interpreter::doFunction(const QString& func, QJSValueList& args)
{
    QString text;
    for (qint32 i = 0; i < args.size(); i++)
    {
        text += args[i].toString() + " ";
    }
#ifdef GAMEDEBUG
    // Console::print("Calling: " + func + " with " + text, Console::eDEBUG);
#endif
    QJSValue ret;
    QJSValue funcPointer = globalObject().property(func);
    if (funcPointer.isCallable())
    {
        ret = funcPointer.call(args);
        if (ret.isError())
        {
            QString error = ret.toString();
            Console::print(error, Console::eERROR);
        }
    }
    else
    {
        QString error = "Error: attemp to call a non function value.";
        Console::print(error, Console::eERROR);
    }
#ifdef GAMEDEBUG
    // Console::print("Result is: " + ret.toString(), Console::eDEBUG);
#endif
    return ret;
}

QJSValue Interpreter::doFunction(const QString& obj, const QString& func, const QJSValueList& args)
{
    QString text;
    for (qint32 i = 0; i < args.size(); i++)
    {
        text += args[i].toString() + " ";
    }
#ifdef GAMEDEBUG
    // Console::print("Calling: " + func + " of " + obj + " with " + text, Console::eDEBUG);
#endif
    QJSValue ret;

    QJSValue objPointer = globalObject().property(obj);
    if (objPointer.isObject())
    {
        QJSValue funcPointer = objPointer.property(func);
        if (funcPointer.isCallable())
        {
            ret = funcPointer.call(args);
            if (ret.isError())
            {
                QString error = ret.toString();
                Console::print(error, Console::eERROR);
            }
        }
        else
        {
            QString error = "Error: attemp to call a non function value.";
            Console::print(error, Console::eERROR);
        }
    }
    else
    {
        QString error = "Error: attemp to call a non object value in order to call a function.";
        Console::print(error, Console::eERROR);
    }
#ifdef GAMEDEBUG
    // Console::print("Result is: " + ret.toString(), Console::eDEBUG);
#endif
    return ret;
}

QJSValue Interpreter::doString(const QString& task)
{
    QJSValue value = evaluate(task, "GameCode");

    if (value.isError())
    {
        Console::print(value.toString(), Console::eERROR);
    }
    else if (!value.isNull() && !value.isUndefined())
    {
        Console::print("Result = " + value.toString(), Console::eDEBUG);
    }
    return value;
}

void Interpreter::pushInt(const QString& name, qint32 value)
{
    globalObject().setProperty(name, value);
}

void Interpreter::pushDouble(const QString& name, double value)
{
    globalObject().setProperty(name, value);
}

void Interpreter::pushString(const QString& name, const QString& value)
{
    globalObject().setProperty(name, value);
}

void Interpreter::pushObject(const QString& name, QObject* object)
{
    QJSValue newQObj = newQObject(object);
    globalObject().setProperty(name, newQObj);
}

QJSValue Interpreter::newQObject(QObject* object)
{
    QJSValue newQObj = QQmlEngine::newQObject(object);
    // make sure js never deletes our qobject since that's kinda not what we want
    QQmlEngine::setObjectOwnership(object, QQmlEngine::ObjectOwnership::CppOwnership);
    return newQObj;
}

void Interpreter::setCppOwnerShip(QObject* object)
{
    QQmlEngine::setObjectOwnership(object, QQmlEngine::ObjectOwnership::CppOwnership);
}

void Interpreter::cleanMemory()
{
    collectGarbage();
}

qint32 Interpreter::getGlobalInt(const QString& var)
{
    qint32 ret = 0;
    QJSValue value = globalObject().property(var);
    if (!value.isNumber())
    {
        QString error = "Error: attemp to read " + var + "which is not from type number.";
        Console::print(error, Console::eERROR);
    }
    else
    {
        ret = value.toInt();
    }
    return ret;
}

bool Interpreter::getGlobalBool(const QString& var)
{
    bool ret = 0;
    QJSValue value = globalObject().property(var);
    if (!value.isBool())
    {
        QString error = "Error: attemp to read " + var + "which is not from type bool.";
        Console::print(error, Console::eERROR);
    }
    else
    {
        ret = value.toBool();
    }
    return ret;
}

double Interpreter::getGlobalDouble(const QString& var)
{
    double ret = 0;
    QJSValue value = globalObject().property(var);
    if (!value.isNumber())
    {
        QString error = "Error: attemp to read " + var + "which is not from type number.";
        Console::print(error, Console::eERROR);
    }
    else
    {
        ret = value.toNumber();
    }
    return ret;
}

QString Interpreter::getGlobalString(const QString& var)
{
    QString ret = "";
    QJSValue value = globalObject().property(var);
    if (!value.isString())
    {
        QString error = "Error: attemp to read " + var + "which is not from type QString.";
        Console::print(error, Console::eERROR);
    }
    else
    {
        ret = value.toString();
    }
    return ret;
}

QJSValue Interpreter::getGlobal(const QString& var)
{
    QJSValue value = globalObject().property(var);
    return value;
}

void Interpreter::setGlobal(const QString& var, QJSValue obj)
{
    globalObject().setProperty(var, obj);
}

void Interpreter::deleteObject(const QString& name)
{
    QString order = "delete " + name + ";";
    doString(order);
}
