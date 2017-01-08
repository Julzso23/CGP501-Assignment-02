#include "Collision\AABB.hpp"
#include "Utility.hpp"

AABB::AABB() :
    size(0.f, 0.f)
{
}

Vector2f AABB::getSize()
{
    return size;
}

void AABB::setSize(Vector2f size)
{
    this->size = size;
}

Vector2f AABB::getHalf()
{
    return size / 2.f;
}

Vector2f AABB::getCentre()
{
    return getPosition() + getHalf();
}

Hit AABB::testIntersection(Vector2f point)
{
    Hit result;
    Vector2f difference = point - getCentre();
    Vector2f collisionPoint = getHalf() - Vector2f(abs(difference.x), abs(difference.y));

    result.object = this;

    if (collisionPoint.x <= 0.f || collisionPoint.y <= 0.f)
    {
        result.hit = false;
        return result;
    }

    if (collisionPoint.x < collisionPoint.y)
    {
        float signX = Utility::sign(difference.x);

        result.delta.x = collisionPoint.x * signX;
        result.delta.y = 0.f;

        result.normal.x = signX;
        result.normal.y = 0.f;

        result.position.x = getCentre().x + (getHalf().x * signX);
        result.position.y = point.y;

        result.hit = true;

        return result;
    }

    float signY = Utility::sign(difference.y);

    result.delta.x = 0.f;
    result.delta.y = collisionPoint.y * signY;

    result.normal.x = 0.f;
    result.normal.y = signY;

    result.position.x = point.x;
    result.position.y = getCentre().y + (getHalf().y * signY);

    result.hit = true;

    return result;
}

Hit AABB::testIntersection(Segment segment, Vector2f padding)
{
    Hit result;

    Vector2f scale = Vector2f(1.f / segment.delta.x, 1.f / segment.delta.y);
    Vector2f sign = Vector2f(Utility::sign(scale.x), Utility::sign(scale.y));

    Vector2f nearTimes, farTimes;

    nearTimes.x = (getCentre().x - sign.x * (getHalf().x + padding.x) - segment.position.x) * scale.x;
    nearTimes.y = (getCentre().y - sign.y * (getHalf().y + padding.y) - segment.position.y) * scale.y;

    farTimes.x = (getCentre().x + sign.x * (getHalf().x + padding.x) - segment.position.x) * scale.x;
    farTimes.y = (getCentre().y + sign.y * (getHalf().y + padding.y) - segment.position.y) * scale.y;

    result.object = this;

    if (nearTimes.x > farTimes.y || nearTimes.y > farTimes.x)
    {
        result.hit = false;
        return result;
    }

    float nearTime = nearTimes.x > nearTimes.y ? nearTimes.x : nearTimes.y;
    float farTime = farTimes.x < farTimes.y ? farTimes.x : farTimes.y;

    if (nearTime >= 1.f || farTime <= 0.f)
    {
        result.hit = false;
        return result;
    }

    result.time = Utility::clamp(nearTime, 0.f, 1.f);

    if (nearTimes.x > nearTimes.y)
    {
        result.normal.x = -sign.x;
        result.normal.y = 0.f;
    }
    else
    {
        result.normal.x = 0.f;
        result.normal.y = -sign.y;
    }

    result.delta = segment.delta * result.time;

    result.position = segment.position + result.delta;

    result.hit = true;

    return result;
}

Hit AABB::testIntersection(AABB& other)
{
    Hit result;

    Vector2f difference = other.getCentre() - getCentre();
    Vector2f collisionPoint = (other.getHalf() + getHalf()) - Vector2f(abs(difference.x), abs(difference.y));

    result.object = this;

    if (collisionPoint.x <= 0.f || collisionPoint.y <= 0.f)
    {
        result.hit = false;
        return result;
    }

    if (collisionPoint.x < collisionPoint.y)
    {
        float signX = Utility::sign(difference.x);

        result.delta.x = collisionPoint.x * signX;
        result.delta.y = 0.f;

        result.normal.x = signX;
        result.normal.y = 0.f;

        result.position.x = getCentre().x + (getHalf().x * signX);
        result.position.y = other.getCentre().y;

        result.hit = true;

        return result;
    }

    float signY = Utility::sign(difference.y);

    result.delta.x = 0.f;
    result.delta.y = collisionPoint.y * signY;

    result.normal.x = 0.f;
    result.normal.y = signY;

    result.position.x = other.getCentre().x;
    result.position.y = getCentre().y + (getHalf().y * signY);

    result.hit = true;

    return result;
}

Sweep AABB::sweepIntersection(AABB& other, Vector2f delta)
{
    Sweep sweep;

    sweep.position = other.getCentre();
    sweep.hit = testIntersection(other);
    if (sweep.hit.hit)
    {
        sweep.time = 0.f;
        return sweep;
    }

    if (delta.x == 0.f && delta.y == 0.f)
    {
        sweep.time = 1.f;
        return sweep;
    }

    sweep.hit = testIntersection({ other.getCentre(), delta }, other.getHalf());

    if (sweep.hit.hit)
    {
        sweep.time = Utility::clamp(sweep.hit.time - 1e-8f, 0.f, 1.f);

        sweep.position = other.getCentre() + delta * sweep.time;

        Vector2f direction = delta.normalise();

        sweep.hit.position += Vector2f(direction.x * other.getHalf().x, direction.y * other.getHalf().y);

        return sweep;
    }

    sweep.position = other.getCentre() + delta;
    sweep.time = 1.f;

    return sweep;
}
