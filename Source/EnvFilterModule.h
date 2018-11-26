/*
  ==============================================================================

    EnvFilterModule.h
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "CustomComponent.h"


// ENV FILTER
class EnvFilterModule : public CustomComponent
{
public:
    EnvFilterModule ( );

    ~EnvFilterModule();
    
    void paint (Graphics& g) override;
    void resized () override;
    
    void comboBoxUpdate( String text );
    
    float getCutoffKnobValue();
    float getResonanceKnobValue();
    ComboBox& getFilterBox();
    String getFilterType();
    
    void setCutoffKnobValue( float v );
    void setResonanceKnobValue( float v );

    
    class LeftSide : public CustomComponent
    {
    public:
        LeftSide( );
        ~LeftSide();

        void paint (Graphics& g) override;        
        void resized () override;
    
        void comboBoxUpdate( String text );
        
        float getCutoffKnobValue();
        float getResonanceKnobValue();
        ComboBox& getFilterBox();
        String getFilterType();
        
        void setCutoffKnobValue( float v );
        void setResonanceKnobValue( float v );
        

    private:
        Slider CutoffKnob;
        Slider ResonanceKnob;
        ComboBox FilterBox;
        
        Label FilterTypeLabel;
        Label CutoffLabel;
        Label ResonanceLabel;

        String filterType;
    };

private:            
    Slider AttackSlider;
    Slider DecaySlider;
    Slider SustainSlider;
    Slider ReleaseSlider;

    Label AttackSliderLabel;
    Label DecaySliderLabel;
    Label SustainSliderLabel;
    Label ReleaseSliderLabel;
	Label TitleLabel;
	
	String Title;

    LeftSide* LeftPanel;
};

