#ifndef STORYBOARD_H_
#define STORYBOARD_H_

#include <boost/python.hpp>
#include <map>
#include <omnetpp.h>
#include "artery/storyboard/EffectStack.h"

namespace Veins
{
class TraCIMobility;
}
class Effect;
class Story;

namespace python = boost::python;

namespace Veins
{
class TraCIScenarioManager;
}

class Storyboard : public cSimpleModule
{
private:

    /**
     * Initializes the Storyboard
     * Handled by Omnet++
     */
    virtual void initialize(int) override;

    /**
     * Recieves messages, sent to the Storyboard
     * Handled by Omnet++
     */
    virtual void handleMessage(cMessage * msg);

    Veins::TraCIScenarioManager* manager;
    python::object module;
    std::vector<std::shared_ptr<Story>> m_stories;
    std::map<Veins::TraCIMobility*, EffectStack> m_affectedCars;

public:
    /**
     * Updates the storyboard by checking all stories
     * Is called each time TraCIScenarioManager processes one omnet step
     */
    void updateStoryboard();

    /**
     * Registers a story created in the python script
     * \param shared_ptr to a story, which should be executed from the storyboard
     */
    void registerStory(std::shared_ptr<Story>);

    /**
     * Adds all effects generated from a story
     * \param list all effects to add, all effects needs to be from the same story and the same car
     */
    void addEffect(const std::vector<std::shared_ptr<Effect>>&);

    /**
     * Removes all Effects from one car related to one Story
     * \param TraciMobility: car from which the Effects should be removed
     * \param Story to remove
     */
    void removeStory(Veins::TraCIMobility*, const Story*);

    /**
     * Checks if a specific Story is already applied on a TraCIMobility
     * \param TraCIMobility which should be tested
     * \param Story that should be tested
     */
    bool storyApplied(Veins::TraCIMobility*, const Story*);

    /**
     * Checks if the story has to be applied or removed
     * Is called from Storyboard::update()
     * param: Veins::TraCIMobility which should be tested if the story is already applied
     * param: bool result of condition test
     * param: Story which was tested in the update function
     */
    void checkCar(Veins::TraCIMobility*, bool, Story*);

    /**
     * Fetches all TraCIMobility vehicles from TraCIScenarioManager
     * \return Vector containing all active TraCIMobiliy vehicles
     */
    std::vector<Veins::TraCIMobility*> getCars();

    /**
     * Fetches a parent cModule of a given cModule
     * \param Child cModule
     * \return Parent cModule
     */
    cModule* getParentModule(cModule*);
};

#endif /* STORYBOARD_H_ */
