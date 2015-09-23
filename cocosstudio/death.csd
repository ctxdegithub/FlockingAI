<GameProjectFile>
  <PropertyGroup Type="Node" Name="death" ID="5b272e58-82ad-47e9-9fd7-178671cdb4aa" Version="2.3.2.3" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="20" Speed="1.0000" ActivedAnimationName="walk">
        <Timeline ActionTag="-1544913030" Property="FileData">
          <TextureFrame FrameIndex="0" Tween="False">
            <TextureFile Type="PlistSubImage" Path="death_walk1.png" Plist="death.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="10" Tween="False">
            <TextureFile Type="PlistSubImage" Path="death_walk2.png" Plist="death.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="20" Tween="False">
            <TextureFile Type="PlistSubImage" Path="death_walk3.png" Plist="death.plist" />
          </TextureFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="walk" StartIndex="0" EndIndex="20">
          <RenderColor A="150" R="165" G="42" B="42" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="3" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="spr_death" ActionTag="-1544913030" Tag="4" IconVisible="False" ctype="SpriteObjectData">
            <Size X="115.0000" Y="136.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="death_walk1.png" Plist="death.plist" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>