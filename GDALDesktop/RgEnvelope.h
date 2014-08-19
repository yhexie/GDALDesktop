#pragma once
class RgEnvelope
{
public:
	double      MinX;
    double      MaxX;
    double      MinY;
    double      MaxY;
	
public:
    RgEnvelope()
    {
        MinX = MaxX = MinY = MaxY = 0;
    }
	 double GetWidth()
     {
		return abs(MaxX - MinX); 
     }

        
    double GetHeight()
    {
		return abs(MaxY - MinY);
    }
   ~RgEnvelope(void)
   {
   }

    int  IsInit() const { return MinX != 0 || MinY != 0 || MaxX != 0 || MaxY != 0; }
    void Merge( RgEnvelope const& sOther ) {
        if( IsInit() )
        {
            MinX = MIN(MinX,sOther.MinX);
            MaxX = MAX(MaxX,sOther.MaxX);
            MinY = MIN(MinY,sOther.MinY);
            MaxY = MAX(MaxY,sOther.MaxY);
        }
        else
        {
            MinX = sOther.MinX;
            MaxX = sOther.MaxX;
            MinY = sOther.MinY;
            MaxY = sOther.MaxY;
        }
    }
    void Merge( double dfX, double dfY ) {
        if( IsInit() )
        {
            MinX = MIN(MinX,dfX);
            MaxX = MAX(MaxX,dfX);
            MinY = MIN(MinY,dfY);
            MaxY = MAX(MaxY,dfY);
        }
        else
        {
            MinX = MaxX = dfX;
            MinY = MaxY = dfY;
        }
    }

    int Intersects(RgEnvelope const& other) const
    {
        return MinX <= other.MaxX && MaxX >= other.MinX && 
               MinY <= other.MaxY && MaxY >= other.MinY;
    }

    int Contains(RgEnvelope const& other) const
    {
        return MinX <= other.MinX && MinY <= other.MinY &&
               MaxX >= other.MaxX && MaxY >= other.MaxY;
    }
};

