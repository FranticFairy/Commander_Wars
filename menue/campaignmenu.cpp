#include "menue/campaignmenu.h"
#include "menue/mainwindow.h"
#include "menue/mapselectionmapsmenue.h"
#include "menue/gamemenue.h"

#include "multiplayer/multiplayermenu.h"

#include "coreengine/mainapp.h"
#include "coreengine/console.h"
#include "coreengine/settings.h"
#include "coreengine/audiothread.h"

#include "game/gamemap.h"
#include "game/gamescript.h"

#include "resource_management/backgroundmanager.h"
#include "resource_management/objectmanager.h"

#include "objects/dialogs/filedialog.h"

CampaignMenu::CampaignMenu(spCampaign campaign, bool multiplayer)
    : QObject(),
      m_Multiplayer(multiplayer)
{
    setObjectName("CampaignMenu");
    Mainapp* pApp = Mainapp::getInstance();
    pApp->pauseRendering();
    this->moveToThread(pApp->getWorkerthread());
    Console::print("Entering Campaign Menue", Console::eDEBUG);

    BackgroundManager* pBackgroundManager = BackgroundManager::getInstance();
    // load background
    oxygine::spSprite sprite = new oxygine::Sprite();
    addChild(sprite);
    oxygine::ResAnim* pBackground = pBackgroundManager->getResAnim("campaignmenu");
    sprite->setResAnim(pBackground);
    // background should be last to draw
    sprite->setPriority(static_cast<qint32>(Mainapp::ZOrder::Background));
    sprite->setScaleX(Settings::getWidth() / pBackground->getWidth());
    sprite->setScaleY(Settings::getHeight() / pBackground->getHeight());

    pApp->getAudioThread()->clearPlayList();
    pApp->getAudioThread()->loadFolder("resources/music/mapselection");
    pApp->getAudioThread()->playRandom();

    oxygine::spButton pButtonExit = ObjectManager::createButton(tr("Exit"));
    pButtonExit->attachTo(this);
    pButtonExit->setPosition(10,
                             Settings::getHeight() - pButtonExit->getHeight() - 10);
    pButtonExit->addEventListener(oxygine::TouchEvent::CLICK, [=](oxygine::Event * )->void
    {
        emit sigExitMenue();
    });
    connect(this, &CampaignMenu::sigExitMenue, this, &CampaignMenu::exitMenue, Qt::QueuedConnection);

    m_pButtonNext = ObjectManager::createButton(tr("Next"));
    m_pButtonNext->setPosition(Settings::getWidth() - 10 - m_pButtonNext->getWidth(), Settings::getHeight() - 10 - m_pButtonNext->getHeight());
    m_pButtonNext->attachTo(this);
    m_pButtonNext->addEventListener(oxygine::TouchEvent::CLICK, [=](oxygine::Event * )->void
    {
        emit buttonNext();
    });
    connect(this, &CampaignMenu::buttonNext, this, &CampaignMenu::slotButtonNext, Qt::QueuedConnection);

    m_pButtonSave = ObjectManager::createButton(tr("Save"));
    m_pButtonSave->setPosition(Settings::getWidth() / 2 - m_pButtonSave->getWidth() / 2, Settings::getHeight() - 10 - m_pButtonSave->getHeight());
    m_pButtonSave->attachTo(this);
    m_pButtonSave->addEventListener(oxygine::TouchEvent::CLICK, [=](oxygine::Event * )->void
    {
        emit sigShowSaveCampaign();
    });
    connect(this, &CampaignMenu::sigShowSaveCampaign, this, &CampaignMenu::showSaveCampaign, Qt::QueuedConnection);


    m_pMapSelectionView = new MapSelectionView();
    m_pMapSelectionView->setCurrentCampaign(campaign);
    addChild(m_pMapSelectionView);
    connect(m_pMapSelectionView->getMapSelection(), &MapSelection::itemChanged, this, &CampaignMenu::mapSelectionItemChanged, Qt::QueuedConnection);
    connect(m_pMapSelectionView->getMapSelection(), &MapSelection::itemClicked, this, &CampaignMenu::mapSelectionItemClicked, Qt::QueuedConnection);

    std::tuple<QString, QStringList> data = campaign->getCampaignMaps();
    m_pMapSelectionView->getMapSelection()->setSelection(std::get<0>(data), std::get<1>(data));
    pApp->continueRendering();
}

void CampaignMenu::exitMenue()
{
    
    Console::print("Leaving Option Menue", Console::eDEBUG);
    oxygine::getStage()->addChild(new MapSelectionMapsMenue());
    oxygine::Actor::detach();
    
}

void CampaignMenu::mapSelectionItemClicked(QString item)
{
    
    QFileInfo info = m_pMapSelectionView->getMapSelection()->getCurrentFolder() + item;
    if (info.isFile())
    {
        emit buttonNext();
    }
    
}

void CampaignMenu::mapSelectionItemChanged(QString item)
{
    
    QFileInfo info = m_pMapSelectionView->getMapSelection()->getCurrentFolder() + item;
    m_pMapSelectionView->loadMap(info);
    
}

void CampaignMenu::slotButtonNext()
{
    
    m_pMapSelectionView->loadCurrentMap();
    if (m_pMapSelectionView->getCurrentMap()->getGameScript()->immediateStart())
    {
        spGameMap pMap = GameMap::getInstance();
        pMap->initPlayersAndSelectCOs();
        pMap->setCampaign(m_pMapSelectionView->getCurrentCampaign());
        pMap->getGameScript()->gameStart();
        pMap->updateSprites();
        // start game
        Console::print("Leaving Campaign Menue", Console::eDEBUG);
        oxygine::getStage()->addChild(new GameMenue(false, nullptr));
        oxygine::Actor::detach();
    }
    else if (m_Multiplayer)
    {
        // todo
    }
    else
    {
        Console::print("Leaving Campaign Menue", Console::eDEBUG);
        oxygine::getStage()->addChild(new MapSelectionMapsMenue(-1, m_pMapSelectionView));
        oxygine::Actor::detach();
    }
    
}

void CampaignMenu::showSaveCampaign()
{
    
    QVector<QString> wildcards;
    wildcards.append("*.camp");
    QString path = QCoreApplication::applicationDirPath() + "/savegames";
    spFileDialog fileDialog = new FileDialog(path, wildcards);
    this->addChild(fileDialog);
    connect(fileDialog.get(),  &FileDialog::sigFileSelected, this, &CampaignMenu::saveCampaign, Qt::QueuedConnection);
    
}

void CampaignMenu::saveCampaign(QString filename)
{
    
    if (filename.endsWith(".camp"))
    {
        QFile file(filename);
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QDataStream stream(&file);
        m_pMapSelectionView->getCurrentCampaign()->serializeObject(stream);
        file.close();
    }
    
}
